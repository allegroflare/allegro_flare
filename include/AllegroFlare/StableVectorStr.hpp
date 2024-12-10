#pragma once



#include <vector>
#include <unordered_map>
#include <stdexcept>
#include <string>



namespace AllegroFlare
{

template <typename valueT>
class StableVectorStr
{
public:
   using key_type = std::string;
   using value_type = valueT;

private:
   std::vector<value_type> data;
   std::unordered_map<key_type, size_t> key_to_index;

public:
   key_type add(const key_type &key, const value_type &value)
   {
      if (key_to_index.find(key) != key_to_index.end())
      {
         throw std::invalid_argument("Key already exists");
      }

      key_to_index[key] = data.size();
      data.push_back(value);
      return key;
   }

   value_type& allocate(const key_type &key)
   {
      if (key_to_index.find(key) != key_to_index.end())
      {
         throw std::invalid_argument("Key already exists");
      }

      key_to_index[key] = data.size();
      data.emplace_back(); // Default-construct the new value
      return data.back();
   }

   void remove(const key_type &key)
   {
      auto it = key_to_index.find(key);
      if (it == key_to_index.end())
      {
         throw std::out_of_range("Invalid key");
      }

      size_t index = it->second;
      size_t last_index = data.size() - 1;

      if (index != last_index)
      {
         // Move the last element to the position of the removed element
         std::swap(data[index], data[last_index]);

         // Update the key of the swapped element
         auto swapped_key = std::find_if(key_to_index.begin(), key_to_index.end(),
                                         [last_index](const auto &pair)
                                         {
                                            return pair.second == last_index;
                                         });

         if (swapped_key != key_to_index.end())
         {
            swapped_key->second = index; // Update the index for the swapped key
         }
      }

      // Remove the last element and erase the key from the map
      data.pop_back();
      key_to_index.erase(it);
   }

   value_type &get(const key_type &key)
   {
      auto it = key_to_index.find(key);
      if (it == key_to_index.end())
      {
         throw std::out_of_range("Invalid key");
      }
      return data[it->second];
   }

   const value_type &get(const key_type &key) const
   {
      auto it = key_to_index.find(key);
      if (it == key_to_index.end())
      {
         throw std::out_of_range("Invalid key");
      }
      return data[it->second];
   }

   std::vector<value_type> &get_data()
   {
      return data;
   }

   size_t size() const
   {
      return data.size();
   }

   bool contains(const key_type &key) const
   {
      return key_to_index.find(key) != key_to_index.end();
   }
};

} // namespace AllegroFlare




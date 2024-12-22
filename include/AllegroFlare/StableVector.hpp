#pragma once


#include <vector>
#include <unordered_map>
#include <stdexcept>
#include <algorithm> // for std::find_if



namespace AllegroFlare {


template <typename valueT>
class StableVector
{
public:
   using key_type = int;
   using value_type = valueT;

private:
   std::vector<value_type> data;
   std::unordered_map<key_type, size_t> key_to_index;
   key_type next_key = 0;

public:
   key_type add(const value_type &value)
   {
      key_type key = next_key++;
      key_to_index[key] = data.size();
      data.push_back(value);
      return key;
   }

   std::pair<key_type, value_type&> allocate()
   {
      key_type key = next_key++;
      key_to_index[key] = data.size();
      data.emplace_back(); // Default-construct the new value
      return {key, data.back()};
   }

   void remove(key_type key)
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

   value_type &get(key_type key)
   {
      auto it = key_to_index.find(key);
      if (it == key_to_index.end())
      {
         throw std::out_of_range("Invalid key");
      }
      return data[it->second];
   }

   const value_type &get(key_type key) const
   {
      auto it = key_to_index.find(key);
      if (it == key_to_index.end())
      {
         throw std::out_of_range("Invalid key");
      }
      return data[it->second];
   }

   std::vector<value_type> &get_data()
   //const std::vector<value_type> &get_data() const
   {
      return data;
   }

   size_t size() const
   {
      return data.size();
   }

   bool contains(key_type key) const
   {
      return key_to_index.find(key) != key_to_index.end();
   }
};


} // namespace AllegroFlare




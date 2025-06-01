#pragma once


#include <vector>
#include <unordered_map>
#include <stdexcept>
#include <algorithm> // for std::swap (though std::move might also be considered)
// #include <utility> // for std::move if you prefer that for specific types


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
   std::vector<key_type> data_index_to_key; // New: Maps data vector's index to its key
   key_type next_key = 0;

public:
   key_type add(const value_type &value)
   {
      key_type key = next_key++;
      size_t new_element_index = data.size(); // Index before push_back

      key_to_index[key] = new_element_index;
      data.push_back(value);
      data_index_to_key.push_back(key); // Store the key for this new index

      return key;
   }

   std::pair<key_type, value_type&> allocate()
   {
      key_type key = next_key++;
      size_t new_element_index = data.size(); // Index before emplace_back

      key_to_index[key] = new_element_index;
      data.emplace_back(); // Default-construct the new value
      data_index_to_key.push_back(key); // Store the key for this new index

      return {key, data.back()};
   }

   void remove(key_type key_to_remove)
   {
      auto key_map_iterator = key_to_index.find(key_to_remove);
      if (key_map_iterator == key_to_index.end())
      {
          throw std::out_of_range("StableVector::remove error: Invalid key provided.");
      }

      size_t index_to_remove = key_map_iterator->second;
      size_t last_data_index = data.size() - 1;

      if (index_to_remove != last_data_index)
      {
          // Element to be removed is not the last one.
          // We need to move the last element into the spot of the removed element.

          // 1. Get the key of the element currently at the end of the 'data' vector.
          // This is O(1) thanks to 'data_index_to_key'.
          key_type key_of_moved_element = data_index_to_key[last_data_index];

          // 2. Move/swap the last data element to the position of the element being removed.
          data[index_to_remove] = std::move(data[last_data_index]); // or std::swap

          // 3. Update the reverse mapping for the moved element in 'data_index_to_key'.
          // The element 'key_of_moved_element' is now at 'index_to_remove'.
          data_index_to_key[index_to_remove] = key_of_moved_element;

          // 4. Update the forward mapping for the moved element in 'key_to_index'.
          // The 'key_of_moved_element' now points to 'index_to_remove'.
          key_to_index[key_of_moved_element] = index_to_remove;
      }
      // If index_to_remove == last_data_index, the element is already at the end,
      // so no swap or mapping update for a moved element is needed.

      // Remove the last element from data and its corresponding key from data_index_to_key.
      data.pop_back();
      data_index_to_key.pop_back();

      // Erase the original key_to_remove from the key_to_index map.
      key_to_index.erase(key_map_iterator); // Use iterator for potentially better performance
   }

   value_type &get(key_type key)
   {
      auto it = key_to_index.find(key);
      if (it == key_to_index.end())
      {
          throw std::out_of_range("StableVector::get error: Invalid key provided.");
      }
      return data[it->second];
   }

   const value_type &get(key_type key) const
   {
      auto it = key_to_index.find(key);
      if (it == key_to_index.end())
      {
          throw std::out_of_range("StableVector::get const error: Invalid key provided.");
      }
      return data[it->second];
   }

   // Consider providing a const version as well
   std::vector<value_type> &get_data()
   {
      return data;
   }
   
   // Example of how a const version might look:
   // const std::vector<value_type>& get_data() const
   // {
   //     return data;
   // }

   // Access to the data_index_to_key vector might be useful for debugging or specific advanced scenarios,
   // but typically it's an internal detail. If exposed, it should likely be const-only.
   // const std::vector<key_type>& get_data_index_to_key_map() const
   // {
   //    return data_index_to_key;
   // }


   size_t size() const
   {
      return data.size();
   }

   bool empty() const
   {
      return data.empty();
   }

   bool contains(key_type key) const
   {
      return key_to_index.count(key) > 0; // .count() is often preferred for const access
   }

   // Suggested 'clear' method (if you add it) would also need to clear 'data_index_to_key'
   void clear()
   {
      data.clear();
      key_to_index.clear();
      data_index_to_key.clear();
      next_key = 0; // Reset if keys can be reused after a clear; otherwise, don't.
   }

   // Suggested 'reserve' method
   void reserve(size_t capacity)
   {
      data.reserve(capacity);
      key_to_index.reserve(capacity); // unordered_map also has reserve
      data_index_to_key.reserve(capacity);
   }
};

} // namespace AllegroFlare



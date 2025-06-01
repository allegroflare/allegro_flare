#pragma once


#include <string>
#include <vector>
#include <unordered_map>
#include <stdexcept>
#include <utility>
#include <AllegroFlare/StableVector.hpp>


namespace AllegroFlare
{


template <typename valueT>
class StableVectorStr
{
   public:
      using key_type = std::string;
      using value_type = valueT;
      using internal_id_type = typename AllegroFlare::StableVector<value_type>::key_type;

   private:
      AllegroFlare::StableVector<value_type> store;
      std::unordered_map<key_type, internal_id_type> key_to_internal_id_map;

   public:
      StableVectorStr() = default;

      key_type add(const key_type& key, const value_type& value)
      {
         if (key_to_internal_id_map.count(key)) {
            throw std::invalid_argument("StableVectorStr::add error: Key '" + key + "' already exists.");
         }
         internal_id_type new_id = store.add(value);
         key_to_internal_id_map[key] = new_id;
         return key;
      }

      template<typename... Args>
      value_type& emplace(const key_type& key, Args&&... args)
      {
         if (key_to_internal_id_map.count(key)) {
            throw std::invalid_argument("StableVectorStr::emplace error: Key '" + key + "' already exists.");
         }
         value_type temp_object(std::forward<Args>(args)...);
         internal_id_type new_id = store.add(std::move(temp_object)); 
         key_to_internal_id_map[key] = new_id;
         return store.get(new_id);
      }
      
      value_type& allocate(const key_type& key)
      {
         if (key_to_internal_id_map.count(key)) {
            throw std::invalid_argument("StableVectorStr::allocate error: Key '" + key + "' already exists.");
         }
         std::pair<internal_id_type, value_type&> allocation_result = store.allocate();
         key_to_internal_id_map[key] = allocation_result.first;
         return allocation_result.second;
      }

      void remove(const key_type& key)
      {
         auto it_key_map = key_to_internal_id_map.find(key);
         if (it_key_map == key_to_internal_id_map.end()) {
            throw std::out_of_range("StableVectorStr::remove error: Key '" + key + "' not found.");
         }
         internal_id_type id_to_remove = it_key_map->second;
         
         store.remove(id_to_remove);
         key_to_internal_id_map.erase(it_key_map);
      }

      value_type& get(const key_type& key)
      {
         auto it_key_map = key_to_internal_id_map.find(key);
         if (it_key_map == key_to_internal_id_map.end()) {
            throw std::out_of_range("StableVectorStr::get error: Key '" + key + "' not found.");
         }
         return store.get(it_key_map->second);
      }

      const value_type& get(const key_type& key) const
      {
         auto it_key_map = key_to_internal_id_map.find(key);
         if (it_key_map == key_to_internal_id_map.end()) {
            throw std::out_of_range("StableVectorStr::get const error: Key '" + key + "' not found.");
         }
         return store.get(it_key_map->second);
      }

      bool contains(const key_type& key) const
      {
         return key_to_internal_id_map.count(key) > 0;
      }

      size_t size() const
      {
         return store.size();
      }

      bool empty() const
      {
         return store.empty();
      }
      
      void clear()
      {
         store.clear();
         key_to_internal_id_map.clear();
      }

      void reserve(size_t capacity)
      {
         store.reserve(capacity);
         key_to_internal_id_map.reserve(capacity);
      }

      std::vector<value_type>& get_data()
      {
         return store.get_data();
      }

      const std::vector<value_type>& get_data() const
      {
         return store.get_data();
      }

      std::vector<std::pair<const key_type*, value_type*>> get_all_key_value_pairs()
      {
         std::vector<std::pair<const key_type*, value_type*>> entries;
         entries.reserve(key_to_internal_id_map.size());
         for (auto& pair_in_map : key_to_internal_id_map)
         {
            entries.emplace_back(&pair_in_map.first, &store.get(pair_in_map.second));
         }
         return entries;
      }

      std::vector<std::pair<const key_type*, const value_type*>> get_all_key_value_pairs() const
      {
         std::vector<std::pair<const key_type*, const value_type*>> entries;
         entries.reserve(key_to_internal_id_map.size());
         for (const auto& pair_in_map : key_to_internal_id_map)
         {
            entries.emplace_back(&pair_in_map.first, &store.get(pair_in_map.second));
         }
         return entries;
      }
};

} // namespace AllegroFlare



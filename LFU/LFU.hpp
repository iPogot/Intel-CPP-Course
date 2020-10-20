#pragma once 

#include <list> 
#include <unordered_map>
#include <iostream>
#include <iterator>


namespace LFU{
    template <typename data, typename id = int> class LFU_Cache {

        public:
            
            LFU_Cache(size_t cache_size) {
                size_ = cache_size;
                num_of_key_ = 0;
                min_freq_ = 1;
            }
            
            int InsertData(const id key, const data elem) {

                if(key_to_freq_.find(key) == key_to_freq_.end()) {
                    return -1;
                } else {
                    lfu_data_.insert({key, elem});
                }
                    
                return 0;
            }

            int GetData(const id key, data& elem) {

                if(lfu_data_.find(key) == lfu_data_.end()) {
                    return -1;
                } else {
                    elem = lfu_data_[key];
                }

                return 0;
            }

            int LookUp(const id key) {
                
                if(key_to_freq_.find(key) == key_to_freq_.end()) {
                    if(!IsFull()) {
                        InsertKey(key, 1);
                    } else {
                        id del_key = freq_to_key_[min_freq_].front();
                        DeleteKey(del_key, min_freq_);
                        InsertKey(key, 1);
                        lfu_data_.erase(del_key);
                    }

                    if(min_freq_ != 1) {
                        min_freq_ = 1;
                    }

                    return 0;
                } else {
                    IncreaseFrequency(key);
                    return 1;
                }

            }

            size_t GetSmallestFrequency() const {

                return min_freq_;

            }

            size_t GetCacheSize() const {

                return size_;

            }

            size_t GetItemsNumInCache() const {

                return num_of_key_;

            }

        private:
            int IsFull() const {
                if (num_of_key_ == size_) {
                    return 1;
                } else {
                    return 0;
                } 
            }

            void IncreaseFrequency(const id key) {

                size_t frequency = key_to_freq_[key];
                DeleteKey(key, key_to_freq_[key]);

                if(!num_of_key_) {
                    min_freq_++;
                }

                InsertKey(key, frequency + 1);

            }

            void InsertKey(const id key, const size_t frequency) {
                key_to_freq_.insert({key, frequency});
                if(freq_to_key_.find(frequency) == freq_to_key_.end()) {
                    std::list<id> elem_list;
                    elem_list.push_back(key);
                    freq_to_key_.insert({frequency, elem_list});
                } else {
                    freq_to_key_[frequency].push_back(key);
                }   
                num_of_key_++;
            }

            void DeleteKey(const id key, const size_t frequency) {
                key_to_freq_.erase(key);
                freq_to_key_[frequency].remove(key);

                if(freq_to_key_[frequency].empty()) {
                    freq_to_key_.erase(frequency);

                    if(min_freq_ == frequency) {
                        min_freq_++;
                    }

                }
                num_of_key_--;

            }
            

            size_t num_of_key_;
            size_t size_;
            size_t min_freq_;
            std::unordered_map<size_t, std::list<id>> freq_to_key_;
            std::unordered_map<id, size_t> key_to_freq_;
            std::unordered_map<id, data> lfu_data_;

    };

}
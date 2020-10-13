#pragma once 

#include <list> 
#include <unordered_map>
#include <iostream>
#include <iterator>


namespace LFU{
    template <typename el_t> class LFU_Cache {

        public:
            
            LFU_Cache(size_t cache_size) {
                size_ = cache_size;
                num_of_elem_ = 0;
                min_freq_ = 1;
            }

            int LookUp(const el_t element) {
                
                if(elem_to_freq_.find(element) == elem_to_freq_.end()) {
                    if(!IsFull()) {
                        InsertElement(element, 1);
                    } else {
                        el_t del_elem = freq_to_elem_[min_freq_].front();
                        DeleteElement(del_elem, min_freq_);
                        InsertElement(element, 1);
                    }

                    if(min_freq_ != 1) {
                        min_freq_ = 1;
                    }

                    return 0;
                } else {
                    IncreaseFrequency(element);
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

                return num_of_elem_;

            }

        private:
            int IsFull() const {
                if (num_of_elem_ == size_) {
                    return 1;
                } else {
                    return 0;
                } 
            }

            void IncreaseFrequency(const el_t element) {

                size_t frequency = elem_to_freq_[element];
                DeleteElement(element, elem_to_freq_[element]);

                if(!num_of_elem_) {
                    min_freq_++;
                }

                InsertElement(element, frequency + 1);

            }

            void InsertElement(const el_t element, const size_t frequency) {
                elem_to_freq_.insert({element, frequency});
                if(freq_to_elem_.find(frequency) == freq_to_elem_.end()) {
                    std::list<el_t> elem_list;
                    elem_list.push_back(element);
                    freq_to_elem_.insert({frequency, elem_list});
                } else {
                    freq_to_elem_[frequency].push_back(element);
                }   
                num_of_elem_++;
            }

            void DeleteElement(const el_t element, const size_t frequency) {
                elem_to_freq_.erase(element);
                freq_to_elem_[frequency].remove(element);
                


                if(freq_to_elem_[frequency].empty()) {
                    freq_to_elem_.erase(frequency);

                    if(min_freq_ == frequency) {
                        min_freq_++;
                    }

                }
                num_of_elem_--;

            }

            size_t num_of_elem_;
            size_t size_;
            size_t min_freq_;
            std::unordered_map<size_t, std::list<el_t>> freq_to_elem_;
            std::unordered_map<el_t, size_t> elem_to_freq_;

    };

}
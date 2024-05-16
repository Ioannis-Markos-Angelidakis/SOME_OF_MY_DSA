#include <print>
#include <span>

int32_t partition(const std::span<int32_t>& nums, const int32_t& low, const int32_t& high) {
    int32_t pivot = nums[high], index = low - 1;

    for(int32_t j = low; j < high ;++j) {
        if(nums[j] <= pivot) {
            ++index;
            std::swap(nums[j], nums[index]);
        }
    }

    ++index;
    std::swap(nums[high], nums[index]);

    return index;
}

void quick_sort(const std::span<int32_t>& nums, const int32_t& low, const int32_t& high) {
    if(low >= high) {
        return;
    }

    int32_t pivot = partition(nums, low, high);
    quick_sort(nums, low, pivot - 1);
    quick_sort(nums, pivot + 1, high);
}

int32_t main() {
    std::array nums {-5, -7, 1, -2, 0, -1};

    std::println("Before: {:n}", nums);
    quick_sort(nums, 0, nums.size() - 1);
    std::println("After:  {:n}", nums);

    return 0;
}
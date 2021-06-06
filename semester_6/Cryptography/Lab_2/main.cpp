#include <array>
#include <random>
#include <chrono>
#include <cstdint>
#include <iostream>

template <std::size_t N>
struct RTEA {
    static_assert(N == 4 || N == 8, "Required size of RTEA key - 128 or 256 bits.");
    std::array<std::uint32_t, N> key;

    std::uint64_t encrypt(std::uint64_t x)
    {
        auto [a, b] = std::pair{std::uint32_t(x >> 32), std::uint32_t(x)};
        for (std::size_t i = 0; i < key.size() * 4 + 32; ++i) {
             b += a + ((a << 6) ^ (a >> 8)) + (key[i % key.size()] + i);
             ++i;
             a += b + ((b << 6) ^ (b >> 8)) + (key[i % key.size()] + i);
        }
        return std:: uint64_t{a} << 32 | b;
    }

    std::uint64_t decrypt(std::uint64_t x)
     {
         auto [a, b] = std::pair{std::uint32_t(x >> 32), std::uint32_t(x)};
         for (std::int64_t i = key.size() * 4 + 31; i >= 0; --i) {
              a -= b + ((b << 6) ^ (b >> 8)) + (key[i % key.size()] + i);
              --i;
              b -= a + ((a << 6) ^ (a >> 8)) + (key[i % key.size()] + i);
         }
         return std::uint64_t{a} << 32 | b;
     }
};

template <typename Int>
Int random_int()
{
    static std::mt19937 gen{std::random_device{}()};
    std::uniform_int_distribution<Int> dist{};
    return dist(gen);
}

void print_and_check(uint64_t x) {
    RTEA<8> rtea{};
    rtea.key = {0x20B94801, 0x84F22364, 0xA2A795BD, 0x7A69A953,
                0x7EFBC60F, 0xA2F47F3E, 0x23637D6, 0xAEDE318E};
    const auto crypted = rtea.encrypt(x);
    const auto decrypted = rtea.decrypt(crypted);

    std::cout << "Number: " << " " << x << std::endl;
    std::cout << "encrypted: " << " " << crypted << std::endl;
    std::cout << "decrypted: " << " " << decrypted << std::endl;
    if (x == decrypted) {
        std::cout << "Test passed: Decripted message matches the original message!" << std::endl;
    } else {
        std::cout << "Test failed." << std::endl;
    }
};

int main() {
    for (auto i = 0; i < 42; ++i) {
        print_and_check(random_int<std::uint64_t>());
    };

    return 0;
}
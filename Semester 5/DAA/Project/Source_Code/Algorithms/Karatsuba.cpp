
#include "Karatsuba.h"

#include <algorithm>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>

namespace
{
    constexpr uint64_t BASE = 1000000000ULL;
    constexpr size_t BASE_DIGITS = 9;
    constexpr size_t KARATSUBA_THRESHOLD = 32;

    using BigInt = std::vector<uint64_t>;

    void trim(BigInt &a)
    {
        while (a.size() > 1 && a.back() == 0)
            a.pop_back();
    }

    BigInt normalize(const std::string &number)
    {
        if (number.empty())
            throw std::invalid_argument("Empty number.");

        for (char c : number)
        {
            if (c < '0' || c > '9')
                throw std::invalid_argument("Invalid decimal number.");
        }

        size_t start = number.find_first_not_of('0');

        if (start == std::string::npos)
            return {0};

        BigInt result;

        for (size_t end = number.size(); end > start;)
        {
            size_t begin =
                (end - start > BASE_DIGITS)
                ? end - BASE_DIGITS
                : start;

            result.push_back(
                std::stoull(number.substr(begin, end - begin))
            );

            end = begin;
        }

        return result;
    }

    BigInt add(const BigInt &a, const BigInt &b)
    {
        BigInt result;
        size_t n = std::max(a.size(), b.size());

        result.resize(n);

        uint64_t carry = 0;

        for (size_t i = 0; i < n; i++)
        {
            uint64_t sum = carry;

            if (i < a.size())
                sum += a[i];

            if (i < b.size())
                sum += b[i];

            result[i] = sum % BASE;
            carry = sum / BASE;
        }

        if (carry)
            result.push_back(carry);

        return result;
    }

    // Assumes a >= b.
    BigInt subtract(const BigInt &a, const BigInt &b)
    {
        BigInt result = a;
        int64_t borrow = 0;

        for (size_t i = 0; i < result.size(); i++)
        {
            int64_t current =
                static_cast<int64_t>(result[i]) - borrow;

            if (i < b.size())
                current -= static_cast<int64_t>(b[i]);

            if (current < 0)
            {
                current += static_cast<int64_t>(BASE);
                borrow = 1;
            }
            else
            {
                borrow = 0;
            }

            result[i] = static_cast<uint64_t>(current);
        }

        trim(result);
        return result;
    }

    BigInt schoolbook(const BigInt &a, const BigInt &b)
    {
        if (a.size() == 1 && a[0] == 0)
            return {0};

        if (b.size() == 1 && b[0] == 0)
            return {0};

        BigInt result(a.size() + b.size(), 0);

        for (size_t i = 0; i < a.size(); i++)
        {
            uint64_t carry = 0;

            for (size_t j = 0; j < b.size(); j++)
            {
                uint64_t current =
                    result[i + j] + a[i] * b[j] + carry;

                result[i + j] = current % BASE;
                carry = current / BASE;
            }

            size_t position = i + b.size();

            while (carry)
            {
                uint64_t current = result[position] + carry;

                result[position] = current % BASE;
                carry = current / BASE;
                position++;
            }
        }

        trim(result);
        return result;
    }

    BigInt slice(const BigInt &a, size_t begin, size_t end)
    {
        if (begin >= a.size())
            return {0};

        end = std::min(end, a.size());

        BigInt result(a.begin() + begin, a.begin() + end);
        trim(result);

        return result;
    }

    BigInt shift(const BigInt &a, size_t positions)
    {
        if (a.size() == 1 && a[0] == 0)
            return {0};

        BigInt result(positions, 0);
        result.insert(result.end(), a.begin(), a.end());

        return result;
    }

    BigInt karatsuba(const BigInt &a, const BigInt &b)
    {
        if (a.size() <= KARATSUBA_THRESHOLD ||
            b.size() <= KARATSUBA_THRESHOLD)
        {
            return schoolbook(a, b);
        }

        size_t n = std::max(a.size(), b.size());
        size_t half = n / 2;

        BigInt aLow = slice(a, 0, half);
        BigInt aHigh = slice(a, half, a.size());

        BigInt bLow = slice(b, 0, half);
        BigInt bHigh = slice(b, half, b.size());

        BigInt z0 = karatsuba(aLow, bLow);
        BigInt z2 = karatsuba(aHigh, bHigh);

        BigInt sumA = add(aLow, aHigh);
        BigInt sumB = add(bLow, bHigh);

        BigInt z1 = karatsuba(sumA, sumB);

        z1 = subtract(z1, z0);
        z1 = subtract(z1, z2);

        BigInt result = add(
            add(z0, shift(z1, half)),
            shift(z2, half * 2)
        );

        trim(result);
        return result;
    }

    std::string toDecimalString(const BigInt &number)
    {
        std::string result = std::to_string(number.back());

        for (size_t i = number.size() - 1; i > 0; i--)
        {
            std::string chunk = std::to_string(number[i - 1]);

            result += std::string(
                BASE_DIGITS - chunk.size(), '0'
            );

            result += chunk;
        }

        return result;
    }
}

std::string multiplyKaratsuba(
    const std::string &a,
    const std::string &b
)
{
    BigInt first = normalize(a);
    BigInt second = normalize(b);

    BigInt product = karatsuba(first, second);

    return toDecimalString(product);
}

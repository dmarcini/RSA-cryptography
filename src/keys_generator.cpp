#include "keys_generator.hpp"

#include <string>
#include <cstdint>
#include <fstream>
#include <utility>
#include <iostream>

#include "math_operations.hpp"


namespace RSA {

bool KeysGenerator::gen_keys(const std::string &path)
{
    // safe value that protects against overflow during calucations
    const auto max_val {std::numeric_limits<int>::max() / 2};

    std::int_fast64_t q = math::generate_prime(max_val / 2, max_val).value();
    std::int_fast64_t p = math::generate_prime(max_val / 2, max_val).value();

    phi_ = (q - 1) * (p - 1);
    n_ = p * q;

    return gen_pub_key(path) && gen_priv_key(path);
}


bool KeysGenerator::gen_pub_key(const std::string &path)
{
    std::int_fast64_t e {};

    for (e = 3; math::coprime(e, phi_) != 1; e += 2);

    pub_key_ = std::make_pair(e, n_);

    return save_key(path, "rsa.pub", pub_key_);
}


bool KeysGenerator::gen_priv_key(const std::string &path)
{
    std::int_fast64_t d {math::mod_inv(pub_key_.first, phi_).value()};

    priv_key_ = std::make_pair(d, n_);

    return save_key(path, "rsa", priv_key_);
}


bool KeysGenerator::save_key(const std::string &path,
                             const std::string &key_name, const Key &key)
{
    std::ofstream ofs;

    !path.empty() ? ofs.open(path + "/" + key_name)
                  : ofs.open("./" + key_name);

    if (ofs.is_open()) {
        // separating 2 part of the key by delimeter: /
        ofs << key.first << '/' << key.second;
        ofs.close();

        return true;
    } else {
        std::cout << "File can't be opened to write.\n";

        return false;
    }
}

}; // namespace RSA

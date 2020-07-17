#include "encryptor_decryptor.hpp"

#include <string>
#include <utility>
#include <cstdint>
#include <iostream>
#include <fstream>

#include "math_operations.hpp"


namespace RSA {

bool encrypt(const std::string &key_path, const std::string &file_path)
{
    const auto msg_to_encrypt {RSA::load_file(file_path)};
    const auto pub_key {RSA::parse_key(key_path)};

    if (msg_to_encrypt.empty() || !pub_key) {
        return false;
    }

    const auto e {pub_key.value().first};
    const auto n {pub_key.value().second};

    const size_t fixed_char_length {std::to_string(n).size()};
    std::string encrypted_msg {};

    // encrypt each char in the message using public key
    for (char msg_char : msg_to_encrypt) {
        try {
            auto t {static_cast<std::int_fast64_t>(msg_char)};
            auto enc_char {math::mod_pow(e, n, t)};

            // encrypted characters with a shorter length than second
            // number from public key are filled with '0' to provide
            // fixed length for all encrypted char (this property is used in
            // decryption)
            encrypted_msg.append(fixed_char_length
                                 - std::to_string(enc_char).size(),
                                 '0').append(std::to_string(enc_char));
        } catch (...) {}
    }

    return RSA::save_file(encrypted_msg, file_path + ".enc");
}


bool decrypt(const std::string &key_path, std::string file_path)
{
    const auto encrypted_msg {RSA::load_file(file_path)};
    const auto priv_key {RSA::parse_key(key_path)};

    if (encrypted_msg.empty() || !priv_key) {
        return false;
    }

    const auto d {priv_key.value().first};
    const auto n {priv_key.value().second};

    const size_t fixed_char_length {std::to_string(n).size()};
    std::string decrypted_msg {};

    // decrypt each encrypted char of fixed length in the message using
    // private key
    for (size_t i {0}; i < encrypted_msg.size(); i += fixed_char_length) {
        try {
            auto c {std::stol(encrypted_msg.substr(i, fixed_char_length))};
            auto t {static_cast<char>(math::mod_pow(d, n, c))};

            decrypted_msg.push_back(t);
        } catch (...) {}
    }

    return RSA::save_file(decrypted_msg,
                          file_path.replace(file_path.find(".enc"), 4, ".dec"));
}


std::string load_file(const std::string &file_path)
{
    std::string msg {};

    if (std::ifstream ifs(file_path); ifs.is_open()) {
        for (std::string line {}; std::getline(ifs, line);) {
            msg.append(line).append("\n");
        }

        ifs.close();
    } else {
        std::cout << "File '" << file_path << "' can't be opened to read.\n";
    }

    return msg;
}


bool save_file(const std::string &encrypted_msg, const std::string &file_path)
{
    if (std::ofstream ofs(file_path); ofs.is_open()) {
        ofs << encrypted_msg;
        ofs.close();

        return true;
    }

    std::cout << "File '" << file_path << "' can't be opened to write.\n";

    return false;
}


std::optional<Key> parse_key(const std::string &key_path)
{
    std::string key_contents {RSA::load_file(key_path)};

    if (key_contents.empty()) {
        return std::nullopt;
    }

    std::size_t delim_pos {key_contents.find('/')};

    return std::make_pair(std::stol(key_contents.substr(0, delim_pos)),
                          std::stol(key_contents.substr(delim_pos + 1)));
}

}; // namespace RSA

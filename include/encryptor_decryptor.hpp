#ifndef ENCRYPTOR_DECRYPTOR_HPP_
#define ENCRYPTOR_DECRYPTOR_HPP_

#include <string>
#include <utility>
#include <cstdint>
#include <optional>


namespace RSA {

using Key = std::pair<std::int_fast64_t, std::int_fast64_t>;

// encrypt text file with public key
bool encrypt(const std::string &key_path, const std::string &file_path);
// decrypt encrypted text file with private key
bool decrypt(const std::string &key_path, std::string file_path);

// parse to Key type from file
std::optional<Key> parse_key(const std::string &key_path);

std::string load_file(const std::string &file_path);

bool save_file(const std::string &encrypted_msg, const std::string &file_path);

}; // namespace RSA

#endif // ENCRYPTOR_DECRYPTOR_HPP_
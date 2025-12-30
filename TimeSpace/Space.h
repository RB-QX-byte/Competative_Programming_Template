#ifndef SPACE_H
#define SPACE_H

#include <cstddef>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>


namespace TimeSpace {

/**
 * @class SpaceAnalyzer
 * @brief Utility for calculating/estimating memory usage
 */
class SpaceAnalyzer {
public:
  // Format bytes to readable string
  static std::string format_bytes(size_t bytes) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2);

    if (bytes >= 1024ULL * 1024 * 1024) {
      oss << (bytes / (1024.0 * 1024.0 * 1024.0)) << " GB";
    } else if (bytes >= 1024 * 1024) {
      oss << (bytes / (1024.0 * 1024.0)) << " MB";
    } else if (bytes >= 1024) {
      oss << (bytes / 1024.0) << " KB";
    } else {
      oss << bytes << " B";
    }
    return oss.str();
  }

  // Get size of any object
  template <typename T> static size_t size_of(const T &obj) {
    return sizeof(obj);
  }

  // Get size of container (base + elements)
  template <typename Container>
  static size_t container_size(const Container &c) {
    return sizeof(c) + sizeof(typename Container::value_type) * c.size();
  }

  // Get size of C-style array
  template <typename T, size_t N>
  static constexpr size_t array_size(const T (&)[N]) {
    return sizeof(T) * N;
  }

  // Print size of object
  template <typename T>
  static void print_size(const std::string &label, const T &obj,
                         std::ostream &out = std::cerr) {
    out << "[SPACE] " << label << ": " << format_bytes(sizeof(obj))
        << std::endl;
  }

  // Print container memory usage
  template <typename Container>
  static void print_container(const std::string &label, const Container &c,
                              std::ostream &out = std::cerr) {
    size_t total = container_size(c);
    out << "[SPACE] " << label << ": " << format_bytes(total) << " ("
        << c.size() << " elements)" << std::endl;
  }

  // Estimate vector memory (with capacity overhead)
  static size_t estimate_vector(size_t element_size, size_t count) {
    size_t capacity = count > 0 ? count * 2 : 0; // typical doubling
    return capacity * element_size + sizeof(void *) * 3;
  }

  // Estimate unordered_map memory
  static size_t estimate_unordered_map(size_t key_size, size_t value_size,
                                       size_t count) {
    size_t bucket_count = static_cast<size_t>(count * 1.5);
    size_t buckets = sizeof(void *) * bucket_count;
    size_t nodes = (key_size + value_size + sizeof(void *) * 2) * count;
    return buckets + nodes;
  }
};

/**
 * @class ScopedSpace
 * @brief RAII-style space reporter - shows memory of variables in scope
 */
class ScopedSpace {
public:
  explicit ScopedSpace(const std::string &label, size_t bytes,
                       std::ostream &out = std::cerr)
      : m_label(label), m_bytes(bytes), m_out(out) {}

  ~ScopedSpace() {
    m_out << "[SPACE] " << m_label << ": "
          << SpaceAnalyzer::format_bytes(m_bytes) << std::endl;
  }

private:
  std::string m_label;
  size_t m_bytes;
  std::ostream &m_out;
};

} // namespace TimeSpace

// Convenience macro to print size of a variable
#define PRINT_SIZE(var) TimeSpace::SpaceAnalyzer::print_size(#var, var)
#define PRINT_CONTAINER(var)                                                   \
  TimeSpace::SpaceAnalyzer::print_container(#var, var)

#endif // SPACE_H

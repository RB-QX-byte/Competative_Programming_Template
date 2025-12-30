#ifndef TIME_H
#define TIME_H

#include <chrono>
#include <functional>
#include <iomanip>
#include <iostream>
#include <string>


namespace TimeSpace {

/**
 * @class Timer
 * @brief Measures execution time of code blocks
 *
 * Usage:
 *   TimeSpace::Timer timer;
 *   timer.start();
 *   // ... code ...
 *   timer.stop();
 *   timer.print("My Algorithm");
 */
class Timer {
public:
  using Clock = std::chrono::high_resolution_clock;
  using TimePoint = std::chrono::time_point<Clock>;

  Timer() : m_running(false), m_has_measurement(false) {}

  void start() {
    m_start = Clock::now();
    m_running = true;
    m_has_measurement = false;
  }

  void stop() {
    if (m_running) {
      m_end = Clock::now();
      m_running = false;
      m_has_measurement = true;
    }
  }

  void reset() {
    m_running = false;
    m_has_measurement = false;
  }

  double elapsed_ns() const {
    if (m_running) {
      auto now = Clock::now();
      return std::chrono::duration<double, std::nano>(now - m_start).count();
    }
    if (m_has_measurement) {
      return std::chrono::duration<double, std::nano>(m_end - m_start).count();
    }
    return 0.0;
  }

  double elapsed_us() const { return elapsed_ns() / 1000.0; }
  double elapsed_ms() const { return elapsed_ns() / 1000000.0; }
  double elapsed_s() const { return elapsed_ns() / 1000000000.0; }

  bool is_running() const { return m_running; }

  void print(const std::string &label = "Execution time",
             std::ostream &out = std::cerr) const {
    out << std::fixed << std::setprecision(4);
    out << "[TIME] " << label << ": " << elapsed_ms() << " ms" << std::endl;
  }

  // Measure a lambda/function
  template <typename Func, typename... Args>
  static double measure(Func &&func, Args &&...args) {
    Timer timer;
    timer.start();
    std::forward<Func>(func)(std::forward<Args>(args)...);
    timer.stop();
    return timer.elapsed_ms();
  }

  template <typename Func, typename... Args>
  static double measure_and_print(const std::string &label, Func &&func,
                                  Args &&...args) {
    double time =
        measure(std::forward<Func>(func), std::forward<Args>(args)...);
    std::cerr << std::fixed << std::setprecision(4);
    std::cerr << "[TIME] " << label << ": " << time << " ms" << std::endl;
    return time;
  }

private:
  TimePoint m_start;
  TimePoint m_end;
  bool m_running;
  bool m_has_measurement;
};

/**
 * @class ScopedTimer
 * @brief RAII timer - auto prints when scope ends
 *
 * Usage:
 *   {
 *       TimeSpace::ScopedTimer t("Sorting");
 *       // ... code ...
 *   } // prints time here
 */
class ScopedTimer {
public:
  explicit ScopedTimer(const std::string &label = "Scoped block",
                       bool print_on_destruct = true)
      : m_label(label), m_print_on_destruct(print_on_destruct) {
    m_timer.start();
  }

  ~ScopedTimer() {
    m_timer.stop();
    if (m_print_on_destruct) {
      m_timer.print(m_label);
    }
  }

  double elapsed_ms() const { return m_timer.elapsed_ms(); }

private:
  std::string m_label;
  Timer m_timer;
  bool m_print_on_destruct;
};

} // namespace TimeSpace

#endif // TIME_H

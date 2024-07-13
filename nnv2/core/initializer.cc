#include <algorithm>
#include <chrono>
#include <random>

#include "initializer.h"

namespace nnv2 {

static void normal_init(std::vector<float> &data, float s) {
    unsigned seed =
        (unsigned)std::chrono::steady_clock::now().time_since_epoch().count();
    std::default_random_engine rng(seed);
    std::normal_distribution<float> dist(0.f, s);
    std::for_each(data.begin(), data.end(), [&](float &e) { e = dist(rng); });
}

static void uniform_init(std::vector<float> &data, float r) {
    unsigned seed =
        (unsigned)std::chrono::steady_clock::now().time_since_epoch().count();
    std::default_random_engine rng(seed);
    std::uniform_real_distribution<float> dist(-r, r);
    std::for_each(data.begin(), data.end(), [&](float &e) { e = dist(rng); });
}

void LecunNormal::initialize(Array *a, int fan_in, int fan_out) const {
    float s = std::sqrt(1.f / fan_in);
    normal_init(a->get_vec(), s);
}

void XavierNormal::initialize(Array *a, int fan_in, int fan_out) const {
    float s = std::sqrt(2.f / (fan_in + fan_out));
    normal_init(a->get_vec(), s);
}

void KaimingNormal::initialize(Array *a, int fan_in, int fan_out) const {
    float s = std::sqrt(2.f / fan_in);
    normal_init(a->get_vec(), s);
}

void SimplyNormal::initialize(Array *a, int fan_in, int fan_out) const {
    normal_init(a->get_vec(), 0.1f);
}

void LecunUniform::initialize(Array *a, int fan_in, int fan_out) const {
    float r = std::sqrt(1.f / fan_in);
    uniform_init(a->get_vec(), r);
}

void XavierUniform::initialize(Array *a, int fan_in, int fan_out) const {
    float r = std::sqrt(6.f / (fan_in + fan_out));
    uniform_init(a->get_vec(), r);
}

void KaimingUniform::initialize(Array *a, int fan_in, int fan_out) const {
    float r = std::sqrt(6.f / fan_in);
    uniform_init(a->get_vec(), r);
}

void SimplyUniform::initialize(Array *a, int fan_in, int fan_out) const {
    uniform_init(a->get_vec(), 0.01f);
}

} // namespace nnv2
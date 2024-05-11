#include <iostream>
#include <chrono>
#include <functional>

class Base {
public:
    virtual void foo() {
        // 가상 함수
    }
};

class Derived : public Base {
public:
    void foo() override {
        // 가상 함수를 오버라이드
    }
};

// CRTP를 사용한 파생 클래스 템플릿 정의
template <typename Derived>
class CRTPBase {
public:
    void foo() {
        static_cast<Derived*>(this)->implementation();
    }

    // Base 클래스에서 구현되지 않은 가상 함수
    void implementation() {
        //std::cout << "Base implementation" << std::endl;
    }
};

class CRTPDerived : public CRTPBase<CRTPDerived> {
public:
    // CRTPBase 클래스의 가상 함수를 오버라이드
    void implementation() {
        //std::cout << "CRTPDerived implementation" << std::endl;
    }
};

int main() {
    const long loopCount = 100000000L;

    Base base;
    Derived derived;
    CRTPDerived crtpDerived;

    auto start = std::chrono::high_resolution_clock::now();
    for (long i = 0; i < loopCount; ++i) {
        base.foo();
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> baseDuration = end - start;
    std::cout << "Base class: " << baseDuration.count() << " seconds" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    for (long i = 0; i < loopCount; ++i) {
        derived.foo();
    }
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> derivedDuration = end - start;
    std::cout << "Derived class: " << derivedDuration.count() << " seconds" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    for (long i = 0; i < loopCount; ++i) {
        crtpDerived.foo();
    }
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> crtpDerivedDuration = end - start;
    std::cout << "CRTPDerived class: " << crtpDerivedDuration.count() << " seconds" << std::endl;

    return 0;
}


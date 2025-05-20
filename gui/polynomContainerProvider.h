#pragma once



class PolynomContainerProvider {
public:
    virtual ~PolynomContainerProvider() = default;
    virtual polynomContainer* getPolynomContainer() = 0;
};
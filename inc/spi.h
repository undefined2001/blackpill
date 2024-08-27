#ifndef _INC_SPI_H_
#define _INC_SPI_H_
#include "stm32f411xe.h"

class Spi
{

public:
    enum Speed : uint32_t
    {
        div2 = 0,
        div4 = 1,
        div8 = 2,
        div16 = 3,
        div32 = 4
    };

    enum Cpol : uint32_t
    {
        cpol_low = 0,
        cpol_high = 1
    };

    enum Cpha : uint32_t
    {
        cpha_low = 0,
        cpha_high = 1
    };

    enum Mode : uint32_t
    {
        slave = 0,
        master = 1
    };
    enum Dff : uint32_t
    {
        dff8 = 0,
        dff16 = 1
    };
    enum Ssm : uint32_t
    {
        hard = 0,
        soft = 1
    };

private:
    SPI_TypeDef *m_pSPI;
    uint32_t m_Mode;
    uint32_t m_Speed;
    uint32_t m_Cpol;
    uint32_t m_Cpha;
    uint32_t m_Dff;
    uint32_t m_Ssm;

private:
    void clock_en();
    void spi_en();
    void spi_di();

public:
    Spi();
    void init();
    void send(uint8_t *pBuffer, uint32_t len);
};

#endif
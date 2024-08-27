#include "spi.h"

void Spi::spi_en()
{
    m_pSPI->CR1 |= SPI_CR1_SPE;
}

void Spi::spi_di()
{
    m_pSPI->CR1 &= ~SPI_CR1_SPE;
}

void Spi::clock_en()
{
    if (m_pSPI == SPI1)
    {
        RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
    }
    else if (m_pSPI == SPI2)
    {
        RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;
    }
    else if (m_pSPI == SPI2)
    {
        RCC->APB1ENR |= RCC_APB1ENR_SPI3EN;
    }
}

Spi::Spi() : m_pSPI(SPI1), m_Mode(Mode::master), m_Speed(Speed::div16), m_Cpol(Cpol::cpol_low), m_Cpha(Cpha::cpha_low), m_Dff(Dff::dff8), m_Ssm(Ssm::soft)
{
}

void Spi::init()
{
    uint32_t temp_reg = 0;

    clock_en(); /*Enabling the SPI Peripheral's clock*/

    spi_di(); /*Disabling SPI to configure*/

    temp_reg |= m_Mode << SPI_CR1_MSTR_Pos; /* Setting the Mode is it master or Slave */

    temp_reg |= m_Cpol << SPI_CR1_CPOL_Pos; /* Setting Clock Polarity High or Low */

    temp_reg |= m_Cpha << SPI_CR1_CPHA_Pos; /* Setting the Clock Phase */

    temp_reg |= m_Speed << SPI_CR1_BR_Pos; /* Setting the SPI Speed */

    temp_reg |= m_Dff << SPI_CR1_DFF_Pos; /* Setting the Data Frame Format is it 8bits or 16bits */

    temp_reg |= m_Ssm << SPI_CR1_SSM_Pos; /* Setting the Slave Management Method is it Software or Hardware*/

    if (m_Ssm == Ssm::soft)
    {
        temp_reg |= 1U << SPI_CR1_SSI_Pos; /* Setting SSI bit value to high so that master can start the communication */
    }
    m_pSPI->CR1 = temp_reg; /* Setting the values to the Control Register 1*/

    spi_en(); /* Enabling the The SPI to Communicate*/
}

void Spi::send(uint8_t *pBuffer, uint32_t len)
{
    while (len--)
    {
        while (!(m_pSPI->SR & SPI_SR_TXE))
            ;
        m_pSPI->DR = *pBuffer;
        pBuffer++;
    }
    while (m_pSPI->SR & SPI_SR_BSY)
        ;
}
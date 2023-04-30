
#ifndef NVMC
#define NVMCo


#define NVMC_BASE _BASE(0x4001E000)
#define NVMC_READY _REG(unsigned, 0x4001E400)
#define NVMC_CONFIG _REG(unsigned, 0x4001E504)
#define NVMC_ERASEPAGE _REG(unsigned, 0x4001E508)
#define NVMC_ICACHECONF _REG(unsigned, 0x4001E540)
#define NVMC_CONFIG_WEN __BIT(0)
#define NVMC_CONFIG_EEN __BIT(1)
#define NVMC_ICACHECONF_CACHEEN __BIT(0)

#endif
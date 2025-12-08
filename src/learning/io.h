#pragma once

#define bitset(arg,bit) ((arg) |= (1<<(bit)))
#define bitclr(arg,bit) ((arg) &= ~(1<<(bit)))
#define bitflp(arg,bit) ((arg) ^= (1<<(bit)))
#define bittst(arg,bit) ((arg) & (1<<(bit)))

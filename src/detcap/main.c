/**
 * @copyright: (c) 2022, Institute for Control Engineering of Machine Tools and Manufacturing Units,
 *             University of Stuttgart
 *             All rights reserved. Licensed under the Apache License, Version 2.0 (the "License");
 *             you may not use this file except in compliance with the License.
 *             You may obtain a copy of the License at
 *                  http://www.apache.org/licenses/LICENSE-2.0
 *             Unless required by applicable law or agreed to in writing, software
 *             distributed under the License is distributed on an "AS IS" BASIS,
 *             WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *             See the License for the specific language governing permissions and
 *             limitations under the License.
 * @author: Marc Fischer <marc.fischer@isw.uni-stuttgart.de>
 * @description: Calculates the metrics and fault simulation for each encoding
 */

#include "helpers.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>

uint8_t enc_res(uint8_t x, uint8_t A)
{
	return x % A;
}
uint8_t enc_inv_res(uint8_t x, uint8_t A)
{
	return A - (x % A);
}
uint8_t enc_ones_comp(uint8_t x, uint8_t A)
{
	return ~x;
}
uint8_t enc_twos_comp(uint8_t x, uint8_t A)
{
	return ~x + 1;
}
uint16_t enc_an(uint16_t x, uint16_t A)
{
	return x * A;
}

uint8_t check_res(uint8_t x, uint8_t x_enc, uint8_t A)
{
	return x % A == x_enc;
}
uint8_t check_inv_res(uint8_t x, uint8_t x_enc, uint8_t A)
{
	return A - (x % A) == x_enc;
}
uint8_t check_ones_comp(uint8_t x, uint8_t x_enc, uint8_t A)
{
	return ~x == x_enc;
}
uint8_t check_twos_comp(uint8_t x, uint8_t x_enc, uint8_t A)
{
	return ~x + 1 == x_enc;
}
uint8_t check_an(uint16_t x, uint16_t x_enc, uint16_t A)
{
	return x_enc % A == 0 && x * A == x_enc;
}

void cd_8bit(uint8_t (*enc_fun)(uint8_t, uint8_t), char *name, bool noA)
{
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("Code distance for %s on 8bit  \n", name);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	int count = 256;
	uint64_t hist[256][9] = { 0 };
	uint64_t minHammingDistance[256];
	for (int i = 0; i < 256; ++i)
		minHammingDistance[i] = INT32_MAX;
	float avgHammingDistance[256] = { 0.0 };
	for (int A = 1; A <= 255; A++) {
		if (noA && A > 1) {
			break;
		}
		int num = 0;
		for (int i = 0; i < count; i++) {
			uint8_t x = i;
			uint8_t x_enc = enc_fun(x, (uint8_t)A);

			int hd = calcHammingDistance8(x_enc, x);
			avgHammingDistance[A] += hd;
			num++;
			hist[A][hd]++;
			if (hd == 0) {
				int dgb_b = 3;
			}
			if (hd < minHammingDistance[A])
				minHammingDistance[A] = hd;
		}
		avgHammingDistance[A] /= num;
	}
	printf("    Code Distance \n");
	if (noA) {
		printf("   | : |           Hamming distance distribution               |  Avg. |\n");
	} else {
		printf(" A | : |           Hamming distance distribution               |  Avg. |\n");
	}
	printf("   | : +-------------------------------------------------------+       |\n");
	printf("   | : | ");
	for (int j = 0; j < 9; j++) {
		printf("%-5d ", j);
	}
	printf("|       |\n");
	printf("---+---+-------------------------------------------------------+-------+\n");
	int maxA = 0;
	int maxCD = 0;
	for (int A = 1; A <= 255; A++) {
		if (noA && A > 1) {
			break;
		}
		if (minHammingDistance[A] > maxCD) {
			maxCD = minHammingDistance[A];
			maxA = A;
		}
		if (noA) {
			printf("   |");
		} else {
			printf("%-3d|", A);
		}
		printf(" %lu | ", minHammingDistance[A]);
		for (int j = 0; j < 9; j++) {
			printf("%-5lu ", hist[A][j]);
		}
		printf("|%7.4f|\n", avgHammingDistance[A]);
	}
	printf("---+---+-------------------------------------------------------+-------+\n");
	if (!noA) {
		printf("Maximum CD %d with A %d \n", maxCD, maxA);
	}

	printf("\n\n\n");
}

void cd_an_sep_8bit()
{
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("Code distance for separate AN on 8bit->16bit  \n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	int count = 256;
	uint64_t hist[256][18] = { 0 };
	float histAvg[256] = { 0.0 };
	for (int A = 1; A <= 255; A++) {
		int minHammingDistance = INT32_MAX;
		double avgHammingDistance = 0;
		int num = 0;
		for (int i = 1; i < count; i++) {
			uint16_t x = i;
			uint16_t x_enc = (uint16_t)x * (uint16_t)A;

			int hd = calcHammingDistance16(x_enc, x);
			avgHammingDistance += hd;
			num++;
			hist[A][hd]++;
			if (hd < minHammingDistance)
				minHammingDistance = hd;
		}
		avgHammingDistance /= num;
		histAvg[A] = avgHammingDistance;
		hist[A][17] = minHammingDistance;
	}
	printf("    Code Distance \n");
	printf(" A | : |                                     Hamming distance distribution                                     |  Avg. |\n");
	printf("   | : +-------------------------------------------------------------------------------------------------------+       |\n");
	printf("   | : | ");
	for (int j = 0; j < 17; j++) {
		printf("%-5d ", j);
	}
	printf("|       |\n");
	printf("---+---+-------------------------------------------------------------------------------------------------------+-------+\n");
	int maxA = 0;
	int maxCD = 0;
	for (int A = 1; A <= 255; A++) {
		if (hist[A][17] > maxCD) {
			maxCD = hist[A][17];
			maxA = A;
		}
		printf("%-3d| %lu | ", A, hist[A][17]);
		for (int j = 0; j < 17; j++) {
			printf("%-5lu ", hist[A][j]);
		}
		printf("|%7.4f|\n", histAvg[A]);
	}
	printf("---+---+-------------------------------------------------------------------------------------------------------+-------+\n");
	printf("Maximum CD %d with A %d \n", maxCD, maxA);
	printf("\n\n\n");
}

void sdc_perm_8bit(uint8_t (*enc_fun)(uint8_t, uint8_t),
		  uint8_t (*check_fun)(uint8_t, uint8_t, uint8_t), char *name,
		  bool noA)
{
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("Perm Stuck-at SDCs for %s on 8bit  \n", name);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	int count = 256;
	uint64_t sdcs[256];
	uint64_t masked[256];
	for (int A = 1; A <= 255; A++) {
		sdcs[A] = 0;
		masked[A] = 0;
		if (noA && A > 1) {
			break;
		}
		printf("#");
		fflush(stdout);
		for (int i = 0; i < count; i++) {
			uint8_t x = i;
			uint8_t x_enc = enc_fun(x, (uint8_t)A);
			for (int j = 0; j < count; j++) {
				for (int k = 0; k < count; k++) {
					uint8_t mask0 = j ^ (j & k);
					uint8_t mask1 = j & k;
					uint8_t stuck_x = x & (~mask0);
					stuck_x = stuck_x | mask1;
					uint8_t stuck_x_enc = x_enc & (~mask0);
					stuck_x_enc = stuck_x_enc | mask1;
					int isMasked_stuck =
						stuck_x == x &&
						stuck_x_enc == x_enc;
					int check_stuck = check_fun(
						stuck_x, stuck_x_enc, A);
					if (isMasked_stuck)
						masked[A]++;
					if (!isMasked_stuck && check_stuck) {
						sdcs[A]++;
					}
				}
			}
		}
	}
	if (!noA) {
		printf(" A |   SDCs   |  Masked   |\n");
	} else {
		printf("   |   SDCs   |  Masked   |\n");
	}
	printf("---+----------+-----------+\n");
	int min = INT32_MAX;
	int minA = 0;
	for (int A = 1; A <= 255; A++) {
		if (noA && A > 1) {
			break;
		}
		int sum0 = 0;
		if (!noA) {
			printf("%-3d|", A);
		} else {
			printf("   |");
		}
		printf(" %-8lu |", sdcs[A]);
		printf(" %-8lu  |\n", masked[A]);
		if (sdcs[A] < min) {
			min = sdcs[A];
			minA = A;
		}
	}
	printf("---+----------+-----------+\n");
	if (!noA) {
		printf("Min SDCs %d for A %d\n", min, minA);
	}
	printf("\n\n\n");
}

uint64_t progress1[256];
uint64_t progress2[256];
uint64_t sdcs[256];
uint64_t masked[256];
void *perm_an_stat_loop(void *data)
{
	while (true) {
		FILE *pFile = fopen("progress.txt", "w");
		if (!pFile) {
			printf("[Error] Could not open files: %s\n",
			       strerror(errno));
			return NULL;
		}
		for (int A = 1; A <= 255; A++) {
			fprintf(pFile, "%-8lu|%-8lu||%-8lu|%-8lu\n",
				progress1[A], progress2[A], sdcs[A], masked[A]);
		}
		fclose(pFile);
		sleep(2);
	}
}

void* perm_an_loop(void *A_data)
{
	int A = *(int *)A_data;
	fflush(stdout);
	sdcs[A] = 0;
	masked[A] = 0;
	progress1[A] = 0;
	for (unsigned int i = 0; i < 256; i++) {
		progress1[A] = i;
		uint16_t x = i;
		uint16_t x_enc = enc_an(x, (uint16_t)A);
		for (unsigned int j = 0; j <= UINT16_MAX; j++) {
			progress2[A] = j;
			for (unsigned int k = 0; k <= UINT16_MAX; k++) {
				uint16_t mask0 = j ^ (j & k);
				uint16_t mask1 = j & k;
				uint16_t stuck_x = x & (~mask0);
				stuck_x = stuck_x | mask1;
				uint16_t stuck_x_enc = x_enc & (~mask0);
				stuck_x_enc = stuck_x_enc | mask1;
				int isMasked_stuck =
					stuck_x == x && stuck_x_enc == x_enc;
				int check_stuck =
					check_an(stuck_x, stuck_x_enc, A);
				if (isMasked_stuck)
					masked[A]++;
				if (!isMasked_stuck && check_stuck) {
					sdcs[A]++;
				}
			}
		}
	}
	return NULL;
}

void sdc_perm_an_8bit()
{
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("Perm Stuck-at SDCs for separate AN on 8bit  \n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

	pthread_t threads[255];
	int As[256];
	for (int A = 1; A <= 255; A++) {
		As[A] = A;
		int res =
			pthread_create(&threads[A], NULL, perm_an_loop, &As[A]);
	}
	pthread_t stat;
	pthread_create(&stat, NULL, perm_an_stat_loop, NULL);

	for (int A = 1; A <= 255; A++) {
		pthread_join(threads[A], NULL);
	}
	printf(" A |   SDCs   |  Masked   |\n");
	printf("---+----------+-----------+\n");
	int min = INT32_MAX;
	int minA = 0;
	for (int A = 1; A <= 255; A++) {
		int sum0 = 0;
		printf("%-3d|", A);
		printf(" %-8lu |", sdcs[A]);
		printf(" %-8lu  |\n", masked[A]);
		if (sdcs[A] < min) {
			min = sdcs[A];
			minA = A;
		}
	}
	printf("---+----------+-----------+\n");
	printf("Min SDCs %d for A %d\n", min, minA);
	printf("\n\n\n");
}

void sdc_trans_8bit(uint8_t (*enc_fun)(uint8_t, uint8_t),
		   uint8_t (*check_fun)(uint8_t, uint8_t, uint8_t), char *name,
		   bool noA)
{
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("Trans. flip SDCs for %s on 8bit  \n", name);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	int count = 256;
	uint64_t sdcs[256];
	uint64_t masked[256];
	for (int A = 1; A <= 255; A++) {
		if (noA && A > 1) {
			break;
		}
		sdcs[A] = 0;
		masked[A] = 0;
		for (int i = 0; i < count; i++) {
			uint8_t x = i;
			uint8_t x_enc = enc_fun(x, (uint8_t)A);
			for (int j = 0; j < count; j++) {
				uint8_t trans_x = x ^ j;
				int isMasked_trans_x = trans_x == x;
				int check_trans_x =
					check_fun(trans_x, x_enc, A);
				if (isMasked_trans_x)
					masked[A]++;
				if (!isMasked_trans_x && check_trans_x) {
					sdcs[A]++;
				}

				uint8_t trans_x_enc = x_enc ^ j;
				int isMasked_trans_x_enc = trans_x_enc == x_enc;
				int check_trans_x_enc =
					check_fun(x, trans_x_enc, A);
				if (isMasked_trans_x_enc)
					masked[A]++;
				if (!isMasked_trans_x_enc &&
				    check_trans_x_enc) {
					sdcs[A]++;
				}
			}
		}
	}

	printf(" A | SDCs  | Masked |\n");
	printf("---+-------+--------+\n");
	int min = INT32_MAX;
	int minA = 0;
	for (int A = 1; A <= 255; A++) {
		if (noA && A > 1) {
			break;
		}
		int sum0 = 0;
		if (noA) {
			printf("   |");
		} else {
			printf("%-3d|", A);
		}
		printf(" %-5lu |", sdcs[A]);
		printf(" %-5lu  |\n", masked[A]);
		if (sdcs[A] < min) {
			min = sdcs[A];
			minA = A;
		}
	}
	printf("---+-------+--------+\n");
	if (!noA) {
		printf("Min SDCs %d for A %d \n", min, minA);
	}
	printf("\n\n\n");
}

void sdc_trans_an_8bit()
{
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("Trans. flip SDCs for separate AN on 8bit  \n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	int count = UINT16_MAX;
	uint64_t sdcs[256];
	uint64_t masked[256];
	for (int A = 1; A <= 255; A++) {
		sdcs[A] = 0;
		masked[A] = 0;
		printf(" #");
		for (int i = 0; i < 256; i++) {
			uint16_t x = i;
			uint16_t x_enc = enc_an(x, A);
			for (int j = 0; j < count; j++) {
				uint16_t trans_x = x ^ j;
				int isMasked_trans_x = trans_x == x;
				int check_trans_x = check_an(trans_x, x_enc, A);
				if (isMasked_trans_x)
					masked[A]++;
				if (!isMasked_trans_x && check_trans_x) {
					sdcs[A]++;
				}

				uint16_t trans_x_enc = x_enc ^ j;
				int isMasked_trans_x_enc = trans_x_enc == x_enc;
				int check_trans_x_enc =
					check_an(x, trans_x_enc, A);
				if (isMasked_trans_x_enc)
					masked[A]++;
				if (!isMasked_trans_x_enc &&
				    check_trans_x_enc) {
					sdcs[A]++;
				}
			}
		}
	}

	printf(" A | SDCs  | Masked |\n");
	printf("---+-------+--------+\n");
	int min = INT32_MAX;
	int minA = 0;
	for (int A = 1; A <= 255; A++) {
		int sum0 = 0;
		printf("%-3d|", A);
		printf(" %-5lu |", sdcs[A]);
		printf(" %-5lu  |\n", masked[A]);
		if (sdcs[A] < min) {
			min = sdcs[A];
			minA = A;
		}
	}
	printf("---+-------+--------+\n");
	printf("Min SDCs %d for A %d \n", min, minA);
	printf("\n\n\n");
}

int main(int argc, char **argv)
{
	if (argc == 2 && strcmp(argv[1], "trans") == 0) {
		sdc_trans_8bit(&enc_res, &check_res, "residue", false);
		sdc_trans_8bit(&enc_inv_res, &check_inv_res, "inverse residue",
			       false);
		sdc_trans_8bit(&enc_ones_comp, &check_ones_comp,
			       "ones' complement", true);
		sdc_trans_8bit(&enc_twos_comp, &check_twos_comp,
			       "two's complement", true);
		sdc_trans_an_8bit();
	} else if (argc == 2 && strcmp(argv[1], "perm") == 0) {
		sdc_perm_8bit(&enc_res, &check_res, "residue", false);
		sdc_perm_8bit(&enc_inv_res, &check_inv_res, "inverse residue",
			      false);
		sdc_perm_8bit(&enc_ones_comp, &check_ones_comp,
			      "ones' complement", true);
		sdc_perm_8bit(&enc_twos_comp, &check_twos_comp,
			      "two's complement", true);
	} else if (argc == 2 && strcmp(argv[1], "perman") == 0) {
		sdc_perm_an_8bit();
	} else if (argc == 2 && strcmp(argv[1], "cd") == 0) {
		cd_an_sep_8bit();
		cd_8bit(&enc_res, "residue", false);
		cd_8bit(&enc_inv_res, "inverse residue", false);
		cd_8bit(&enc_ones_comp, "ones' complement", true);
		cd_8bit(&enc_twos_comp, "two's complement", true);
	} else {
		printf("%s -- HELP\n", argv[0]);
		printf("use the following arguments to calculate the metrics and fault simulations\n");
		printf("\t detcap cd - calcs the code distance C_d and hamming distances\n");
		printf("\t detcap trans - calcs the transient fault simulation\n");
		printf("\t detcap perm - calcs the permanent fault simulation\n");
		printf("\t detcap perman - calcs the permanent fault simulation for AN-Coding\n");
	}
	return 0;
}
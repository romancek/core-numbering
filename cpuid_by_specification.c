#define _GNU_SOURCE
#include <stdio.h>   // 標準入出力関数を使用するためのヘッダー
#include <stdint.h>  // 固定幅整数型を使用するためのヘッダー
#include <sched.h>   // 現在実行中のCPUコア番号を取得する

// CPUID命令を実行するための関数
void cpuid(uint32_t leaf, uint32_t subleaf, uint32_t *eax, uint32_t *ebx, uint32_t *ecx, uint32_t *edx) {
  // GCCのインラインアセンブリを使用してCPUID命令を実行
  __asm__ __volatile__ (
      "cpuid"
      : "=a" (*eax), "=b" (*ebx), "=c" (*ecx), "=d" (*edx)  // 出力オペランド
      : "a" (leaf), "c" (subleaf)  // 入力オペランド
  );
}

// x2APIC IDからprocessor idとcore idを抽出する関数
void extract_ids(uint32_t *x2apic_id, uint32_t *smt_id, uint32_t *core_id, uint32_t *pkg_id) {
  uint32_t eax, ebx, ecx, edx;
  uint32_t SMT_Mask_Width = 0;
  uint32_t SMT_Select_Mask = 0;
  uint32_t CorePlus_Mask_Width = 0;
  uint32_t CoreOnly_Select_Mask = 0;
  uint32_t Pkg_Select_Mask = 0;

  // x2APIC IDを取得
  cpuid(0xB, 0, &eax, &ebx, &ecx, &edx);
  *x2apic_id = edx;  // EDXレジスタにx2APIC IDが格納される

  // レベル0(SMT)のビット幅を取得
  SMT_Mask_Width = eax & 0x1F;  // 下位5ビットがビット幅
  SMT_Select_Mask = ~((0xffffffff) << SMT_Mask_Width);
  *smt_id = *x2apic_id & SMT_Select_Mask;

  // レベル1(Core)のビット幅を取得
  cpuid(0xB, 1, &eax, &ebx, &ecx, &edx);
  CorePlus_Mask_Width = eax & 0x1F;  // 下位5ビットがビット幅
  CoreOnly_Select_Mask = (~((0xffffffff) << CorePlus_Mask_Width))^SMT_Select_Mask;
  *core_id = (*x2apic_id & CoreOnly_Select_Mask) >> SMT_Mask_Width;  // コアIDを抽出

  Pkg_Select_Mask = (0xffffffff) << CorePlus_Mask_Width;
  *pkg_id = (*x2apic_id & Pkg_Select_Mask) >> CorePlus_Mask_Width;

  // Debug info
  /* printf("SMT_Mask_Width=0x%x, SMT_Select_Mask=0x%x, CorePlus_Mask_Width=0x%x, CoreOnly_Select_Mask=0x%x, Pkg_Select_Mask=0x%x\n",
    SMT_Mask_Width, SMT_Select_Mask, CorePlus_Mask_Width, CoreOnly_Select_Mask, Pkg_Select_Mask);
  */
}

int main() {
  int cpu = sched_getcpu();
  uint32_t x2apic_id, smt_id, core_id, pkg_id;

  // x2APIC IDからprocessor idとcore idを抽出
  extract_ids(&x2apic_id, &smt_id, &core_id, &pkg_id);

  printf("%d\t%u\t\t%u\t%u\t%u\n", cpu, x2apic_id, smt_id, core_id, pkg_id);

  return 0;
}


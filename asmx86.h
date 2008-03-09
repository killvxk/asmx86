// Copyright (c) 2006, Rusty Wagner
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without modification, are permitted provided that
// the following conditions are met:
//
//    * Redistributions of source code must retain the above copyright notice, this list of conditions and the
//      following disclaimer.
//    * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and
//      the following disclaimer in the documentation and/or other materials provided with the distribution.
//    * Neither the name of the author nor the names of its contributors may be used to endorse or promote
//      products derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
// PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#ifndef __ASMX86_H__
#define __ASMX86_H__

#ifndef _MSC_VER
	#ifndef __cplusplus
		#include <stdbool.h>
	#endif
	#include <sys/types.h>
#else
	#ifndef __cplusplus
		typedef unsigned char bool;
		#define true 1
		#define false 0
	#endif
	typedef ptrdiff_t ssize_t;
#endif

#ifndef WIN32
#include <unistd.h>
#endif

#undef IN
#undef OUT


typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;
typedef char int8;
typedef short int16;
typedef int int32;
typedef long long int64;


#define X86_FLAG_LOCK		1
#define X86_FLAG_REP		2
#define X86_FLAG_REPNE		4
#define X86_FLAG_REPE		8
#define X86_FLAG_OPSIZE		16
#define X86_FLAG_ADDRSIZE	32

#define X86_FLAG_INSUFFICIENT_LENGTH	0x80000000

#define X86_FLAG_ANY_REP	(X86_FLAG_REP | X86_FLAG_REPE | X86_FLAG_REPNE)


#ifdef __cplusplus
namespace asmx86
{
#endif
	enum InstructionOperation
	{
		// Independent operations
		INVALID = 0, AAA, AAD, AAM, AAS, ADD, ADC, AND, ARPL, BLENDPD, BLENDPS, BLENDVPD, BLENDVPS,
		BOUND, BSF, BSR, BSWAP, BT, BTC, BTR, BTS,
		CALLF, CALLN, CLC, CLD, CLFLUSH, CLI,
		CLTS, CMC, CMP, CMPXCH16B, CMPXCH8B, CMPXCHG, CPUID, CRC32,
		DAA, DAS, DEC, DIV, DPPD, DPPS, EMMS, ENTER, F2XM1, FABS, FADD, FADDP, FBLD, FBSTP, FCHS, FCLEX,
		FCMOVB, FCMOVBE, FCMOVE, FCMOVNB, FCMOVNBE, FCMOVNE, FCMOVNU, FCMOVU,
		FCOM, FCOMI, FCOMIP, FCOMP, FCOMPP, FCOS,
		FDECSTP, FDISI, FDIV, FDIVP, FDIVR, FDIVRP, FEMMS, FENI, FFREE, FFREEP, FIADD, FICOM, FICOMP, FIDIV, FIDIVR, FILD,
		FIMUL, FINCSTP, FINIT, FIST, FISTP, FISTTP, FISUB, FISUBR,
		FLD, FLD1, FLDCW, FLDENV, FLDL2E, FLDL2T, FLDLG2, FLDLN2, FLDPI, FLDZ,
		FMUL, FMULP, FNOP, FPATAN, FPREM, FPREM1, FPTAN, FRICHOP, FRINEAR, FRINT2, FRNDINT, FRSTOR, FRSTPM,
		FSAVE, FSCALE, FSETPM, FSIN, FSINCOS, FSQRT,
		FST, FSTCW, FSTDW, FSTENV, FSTP, FSTSG, FSTSW, FSUB, FSUBP, FSUBR, FSUBRP,
		FTST, FUCOM, FUCOMI, FUCOMIP, FUCOMP, FUCOMPP, FWAIT, FXAM, FXCH, FXRSTOR, FXSAVE, FXTRACT, FYL2X, FYL2XP1,
		GETSEC, HLT, IDIV, IMUL, IN, INC, INT, INT1, INT3, INTO, INVD, INVLPG, IRET, JMPF, JMPN,
		LAHF, LAR, LDMXCSR, LDS, LEA, LEAVE, LES, LFENCE, LFS, LGS,
		LOOP, LOOPE, LOOPNE, LSL, LSS, MFENCE, MOV, MOVNTI, MOVSS, MOVSX, MOVUPD, MOVUPS, MOVZX,
		MPSADBW, MUL, NEG, NOP, NOT, OR, OUT, PACKSSDW, PACKSSWB, PACKUSDW, PACKUSWB, PABSB, PABSD, PABSW,
		PADDB, PADDD, PADDQ, PADDW, PADDSB, PADDSW, PADDUSB, PADDUSW, PALIGNR,
		PAND, PANDN, PAUSE, PAVGB, PAVGUSB, PAVGW, PBLENDVB, PBLENDW,
		PCMPEQB, PCMPEQD, PCMPEQQ, PCMPEQW, PCMPESTRI, PCMPESTRM, PCMPGTB, PCMPGTD, PCMPGTQ, PCMPGTW,
		PCMPISTRI, PCMPISTRM, PF2ID, PF2IW, PFACC, PFADD, PFCMPEQ, PFCMPGE, PFCMPGT, PFMAX, PFMIN,
		PFMUL, PFNACC, PFPNACC, PFRCP, PFRCPIT1, PFRCPIT2, PFRCPV, PFRSQIT1, PFRSQRT, PFRSQRTV, PFSUB,
		PFSUBR, PHADDD, PHADDSW, PHADDW, PHMINPOSUW, PHSUBD, PHSUBSW, PHSUBW,
		PI2FD, PI2FW, PMADDWD, PMADDUBSW, PMAXSB, PMAXSD, PMAXSW, PMAXUB, PMAXUD, PMAXUW,
		PMINSB, PMINSD, PMINSW, PMINUB, PMINUD, PMINUW,
		PMULDQ, PMULHRSW, PMULHRW, PMULHUW, PMULHW, PMULLD, PMULLW, PMULUDQ,
		POP, POPCNT, POR, PSADBW, PSHUFB, PSIGNB, PSIGND, PSIGNW, PSLLD, PSLLDQ, PSLLQ, PSLLW,
		PSRAD, PSRAW, PSRLD, PSRLDQ, PSRLQ, PSRLW, PSUBB, PSUBD, PSUBQ, PSUBW, PSUBSB, PSUBSW, PSUBUSB, PSUBUSW,
		PSWAPD, PTEST, PUNPCKHBW, PUNPCKHDQ, PUNPCKHQDQ, PUNPCKHWD, PUNPCKLQDQ,
		PUSH, PXOR, RDMSR, RDPMC, RDTSC, RETF, RETN, RCL, RCR, ROL, ROR, ROUNDPS, ROUNDPD, RSM,
		SAHF, SALC, SAR, SBB, SFENCE, SHL, SHLD, SHR, SHRD,
		SUB, STC, STD, STI, STMXCSR, SYSCALL, SYSENTER, SYSEXIT, SYSRET, TEST, UD2,
		VMREAD, VMWRITE, WBINVD, WRMSR, XCHG, XLAT, XADD, XOR, XRSTOR, XSAVE,

		// Grouped operations (ordering within each line is critical)
		ADDPS, ADDPD, ADDSD, ADDSS, ADDSUBPD, ADDSUBPS,
		ANDNPS, ANDNPD,
		ANDPS, ANDPD,
		CBW, CWDE, CDQE,
		CMPSB, CMPSW, CMPSD, CMPSQ,
		CMOVO, CMOVNO, CMOVB, CMOVAE, CMOVE, CMOVNE, CMOVBE, CMOVA, CMOVS, CMOVNS, CMOVPE, CMOVPO, CMOVL, CMOVGE, CMOVLE, CMOVG,
		CWD, CDQ, CQO,
		DIVPS, DIVPD, DIVSD, DIVSS,
		INSB, INSW, INSD, INSQ,
		JCXZ, JECXZ, JRCXZ,
		JO, JNO, JB, JAE, JE, JNE, JBE, JA, JS, JNS, JPE, JPO, JL, JGE, JLE, JG,
		LODSB, LODSW, LODSD, LODSQ,
		MAXPS, MAXPD, MAXSD, MAXSS,
		MINPS, MINPD, MINSD, MINSS,
		MOVD, MOVQ,
		MOVSB, MOVSW, MOVSD, MOVSQ,
		MULPS, MULPD, MULSD, MULSS,
		ORPS, ORPD,
		OUTSB, OUTSW, OUTSD, OUTSQ,
		PEXTRD, PEXTRQ,
		PINSRD, PINSRQ,
		POPA, POPAD,
		POPF, POPFD, POPFQ,
		PUSHA, PUSHAD,
		PUSHF, PUSHFD, PUSHFQ,
		RCPPS, RCPSS,
		RSQRTPS, RSQRTSS,
		SCASB, SCASW, SCASD, SCASQ,
		SETO, SETNO, SETB, SETAE, SETE, SETNE, SETBE, SETA, SETS, SETNS, SETPE, SETPO, SETL, SETGE, SETLE, SETG,
		SQRTPS, SQRTPD, SQRTSD, SQRTSS,
		STOSB, STOSW, STOSD, STOSQ,
		SUBPS, SUBPD, SUBSD, SUBSS,
		XORPS, XORPD,

		// Operations that do not need to be in the first 512 (MMX/SSE operations in table)
		CMPPD, CMPPS, CMPSS,
		COMISD, COMISS,
		CVTDQ2PD, CVTDQ2PS, CVTPD2DQ, CVTPD2PI, CVTPD2PS, CVTPI2PD, CVTPI2PS, CVTPS2DQ, CVTPS2PD, CVTPS2PI,
		CVTSD2SI, CVTSD2SS, CVTSI2SD, CVTSI2SS, CVTSS2SD, CVTSS2SI,
		CVTTPD2DQ, CVTTPD2PI, CVTTPS2DQ, CVTTPS2PI, CVTTSD2SI, CVTTSS2SI, EXTRACTPS,
		HADDPD, HADDPS, HSUBPD, HSUBPS,	INSERTPS, LDDQU, LGDT, LIDT, LLDT, LMSW, LTR,
		MASKMOVQ, MASKMOVDQU, MMXNOP, MONITOR, MOVAPD, MOVAPS, MOVDDUP, MOVDQ2Q, MOVDQA, MOVDQU, MOVHLPS, MOVHPD, MOVHPS,
		MOVSHDUP, MOVSLDUP, MOVLHPS, MOVLPD, MOVLPS,
		MOVMSKPD, MOVMSKPS, MOVNTDQ, MOVNTDQA, MOVNTPD, MOVNTPS, MOVNTQ, MOVQ2DQ, MWAIT,
		PINSRB, PINSRW, PEXTRB, PEXTRW, PMOVMSKB, PMOVSXBD, PMOVSXBQ, PMOVSXDQ, PMOVSXBW, PMOVSXWD, PMOVSXWQ,
		PMOVZXBD, PMOVZXBQ, PMOVZXDQ, PMOVZXBW, PMOVZXWD, PMOVZXWQ,
		PREFETCH, PREFETCHNTA, PREFETCHT0, PREFETCHT1, PREFETCHT2, PREFETCHW, PSHUFD, PSHUFHW, PSHUFLW, PSHUFW,
		PUNPCKLBW, PUNPCKLDQ, PUNPCKLWD, ROUNDSD, ROUNDSS,
		SGDT, SIDT, SLDT, SHUFPD, SHUFPS, SMSW, STR, SWAPGS,
		UCOMISD, UCOMISS, UNPCKHPD, UNPCKHPS, UNPCKLPD, UNPCKLPS, VERR, VERW,
		VMCALL, VMCLEAR, VMLAUNCH, VMPTRLD, VMPTRST, VMRESUME, VMXOFF, VMXON, XGETBV, XSETBV
	};
#ifndef __cplusplus
	typedef enum InstructionOperation InstructionOperation;
#endif


	enum SegmentRegister
	{
		SEG_ES = 0, SEG_CS = 1, SEG_SS = 2, SEG_DS = 3, SEG_FS = 4, SEG_GS = 5,
		SEG_DEFAULT = 7
	};
#ifndef __cplusplus
	typedef enum SegmentRegister SegmentRegister;
#endif


#ifdef X86_ALT_OPERAND_NAMES
#define __X86_OPER(n) X86_ ## n
#else
#define __X86_OPER(n) n
#endif

	enum OperandType
	{
		NONE = 0, IMM, MEM,
		__X86_OPER(REG_AL), __X86_OPER(REG_CL), __X86_OPER(REG_DL), __X86_OPER(REG_BL), __X86_OPER(REG_AH), __X86_OPER(REG_CH), __X86_OPER(REG_DH), __X86_OPER(REG_BH),
		__X86_OPER(REG_SPL), __X86_OPER(REG_BPL), __X86_OPER(REG_SIL), __X86_OPER(REG_DIL),
		__X86_OPER(REG_R8B), __X86_OPER(REG_R9B), __X86_OPER(REG_R10B), __X86_OPER(REG_R11B), __X86_OPER(REG_R12B), __X86_OPER(REG_R13B), __X86_OPER(REG_R14B), __X86_OPER(REG_R15B),
		__X86_OPER(REG_AX), __X86_OPER(REG_CX), __X86_OPER(REG_DX), __X86_OPER(REG_BX), __X86_OPER(REG_SP), __X86_OPER(REG_BP), __X86_OPER(REG_SI), __X86_OPER(REG_DI),
		__X86_OPER(REG_R8W), __X86_OPER(REG_R9W), __X86_OPER(REG_R10W), __X86_OPER(REG_R11W), __X86_OPER(REG_R12W), __X86_OPER(REG_R13W), __X86_OPER(REG_R14W), __X86_OPER(REG_R15W),
		__X86_OPER(REG_EAX), __X86_OPER(REG_ECX), __X86_OPER(REG_EDX), __X86_OPER(REG_EBX), __X86_OPER(REG_ESP), __X86_OPER(REG_EBP), __X86_OPER(REG_ESI), __X86_OPER(REG_EDI),
		__X86_OPER(REG_R8D), __X86_OPER(REG_R9D), __X86_OPER(REG_R10D), __X86_OPER(REG_R11D), __X86_OPER(REG_R12D), __X86_OPER(REG_R13D), __X86_OPER(REG_R14D), __X86_OPER(REG_R15D),
		__X86_OPER(REG_RAX), __X86_OPER(REG_RCX), __X86_OPER(REG_RDX), __X86_OPER(REG_RBX), __X86_OPER(REG_RSP), __X86_OPER(REG_RBP), __X86_OPER(REG_RSI), __X86_OPER(REG_RDI),
		__X86_OPER(REG_R8), __X86_OPER(REG_R9), __X86_OPER(REG_R10), __X86_OPER(REG_R11), __X86_OPER(REG_R12), __X86_OPER(REG_R13), __X86_OPER(REG_R14), __X86_OPER(REG_R15),
		__X86_OPER(REG_ST0), __X86_OPER(REG_ST1), __X86_OPER(REG_ST2), __X86_OPER(REG_ST3), __X86_OPER(REG_ST4), __X86_OPER(REG_ST5), __X86_OPER(REG_ST6), __X86_OPER(REG_ST7),
		__X86_OPER(REG_MM0), __X86_OPER(REG_MM1), __X86_OPER(REG_MM2), __X86_OPER(REG_MM3), __X86_OPER(REG_MM4), __X86_OPER(REG_MM5), __X86_OPER(REG_MM6), __X86_OPER(REG_MM7),
		__X86_OPER(REG_XMM0), __X86_OPER(REG_XMM1), __X86_OPER(REG_XMM2), __X86_OPER(REG_XMM3), __X86_OPER(REG_XMM4), __X86_OPER(REG_XMM5), __X86_OPER(REG_XMM6), __X86_OPER(REG_XMM7),
		__X86_OPER(REG_XMM8), __X86_OPER(REG_XMM9), __X86_OPER(REG_XMM10), __X86_OPER(REG_XMM11), __X86_OPER(REG_XMM12), __X86_OPER(REG_XMM13), __X86_OPER(REG_XMM14), __X86_OPER(REG_XMM15),
		__X86_OPER(REG_CR0), __X86_OPER(REG_CR1), __X86_OPER(REG_CR2), __X86_OPER(REG_CR3), __X86_OPER(REG_CR4), __X86_OPER(REG_CR5), __X86_OPER(REG_CR6), __X86_OPER(REG_CR7),
		__X86_OPER(REG_CR8), __X86_OPER(REG_CR9), __X86_OPER(REG_CR10), __X86_OPER(REG_CR11), __X86_OPER(REG_CR12), __X86_OPER(REG_CR13), __X86_OPER(REG_CR14), __X86_OPER(REG_CR15),
		__X86_OPER(REG_DR0), __X86_OPER(REG_DR1), __X86_OPER(REG_DR2), __X86_OPER(REG_DR3), __X86_OPER(REG_DR4), __X86_OPER(REG_DR5), __X86_OPER(REG_DR6), __X86_OPER(REG_DR7),
		__X86_OPER(REG_DR8), __X86_OPER(REG_DR9), __X86_OPER(REG_DR10), __X86_OPER(REG_DR11), __X86_OPER(REG_DR12), __X86_OPER(REG_DR13), __X86_OPER(REG_DR14), __X86_OPER(REG_DR15),
		__X86_OPER(REG_TR0), __X86_OPER(REG_TR1), __X86_OPER(REG_TR2), __X86_OPER(REG_TR3), __X86_OPER(REG_TR4), __X86_OPER(REG_TR5), __X86_OPER(REG_TR6), __X86_OPER(REG_TR7),
		__X86_OPER(REG_TR8), __X86_OPER(REG_TR9), __X86_OPER(REG_TR10), __X86_OPER(REG_TR11), __X86_OPER(REG_TR12), __X86_OPER(REG_TR13), __X86_OPER(REG_TR14), __X86_OPER(REG_TR15),
		__X86_OPER(REG_ES), __X86_OPER(REG_CS), __X86_OPER(REG_SS), __X86_OPER(REG_DS), __X86_OPER(REG_FS), __X86_OPER(REG_GS)
	};
#ifndef __cplusplus
	typedef enum OperandType OperandType;
#endif


	struct InstructionOperand
	{
		OperandType operand;
		OperandType components[2];
		uint8 scale;
		uint16 size;
		int64 immediate;
		SegmentRegister segment;
	};
#ifndef __cplusplus
	typedef struct InstructionOperand InstructionOperand;
#endif


	struct Instruction
	{
		InstructionOperation operation;
		InstructionOperand operands[3];
		uint32 flags;
		SegmentRegister segment;
		size_t length;
	};
#ifndef __cplusplus
	typedef struct Instruction Instruction;
#endif


#ifdef __cplusplus
	extern "C"
	{
#endif
		bool Disassemble16(const uint8* opcode, uint64 addr, size_t maxLen, Instruction* result);
		bool Disassemble32(const uint8* opcode, uint64 addr, size_t maxLen, Instruction* result);
		bool Disassemble64(const uint8* opcode, uint64 addr, size_t maxLen, Instruction* result);

		size_t FormatInstructionString(char* out, size_t outMaxLen, const char* fmt, const uint8* opcode,
			uint64 addr, const Instruction* instr);

		size_t DisassembleToString16(char* out, size_t outMaxLen, const char* fmt, const uint8* opcode,
			uint64 addr, size_t maxLen, Instruction* instr);
		size_t DisassembleToString32(char* out, size_t outMaxLen, const char* fmt, const uint8* opcode,
			uint64 addr, size_t maxLen, Instruction* instr);
		size_t DisassembleToString64(char* out, size_t outMaxLen, const char* fmt, const uint8* opcode,
			uint64 addr, size_t maxLen, Instruction* instr);
#ifdef __cplusplus
	}
}
#endif


#ifndef X86_ALT_OPERAND_NAMES // Code generator does not support altername naming

#define __CODEGENX86_32BIT
#include "codegenx86.h"
#undef __CODEGENX86_32BIT

#define __CODEGENX86_64BIT
#include "codegenx86.h"
#undef __CODEGENX86_64BIT

#endif


#endif


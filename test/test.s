	.file	"test.cpp"
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.section	.text._ZN12TmDataCenterC2Ev,"axG",@progbits,_ZN12TmDataCenterC5Ev,comdat
	.align 2
	.weak	_ZN12TmDataCenterC2Ev
	.type	_ZN12TmDataCenterC2Ev, @function
_ZN12TmDataCenterC2Ev:
.LFB974:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movl	$1, %edi
	call	_Znwm
	movq	-8(%rbp), %rdx
	movq	%rax, (%rdx)
	movl	$1, %edi
	call	_Znwm
	movq	-8(%rbp), %rdx
	movq	%rax, 8(%rdx)
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE974:
	.size	_ZN12TmDataCenterC2Ev, .-_ZN12TmDataCenterC2Ev
	.weak	_ZN12TmDataCenterC1Ev
	.set	_ZN12TmDataCenterC1Ev,_ZN12TmDataCenterC2Ev
	.section	.rodata
.LC0:
	.string	"Jack"
	.text
	.globl	main
	.type	main, @function
main:
.LFB982:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA982
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r12
	pushq	%rbx
	subq	$48, %rsp
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	movl	$16, %edi
.LEHB0:
	call	_Znwm
.LEHE0:
	movq	%rax, %rbx
	movq	%rbx, %rdi
.LEHB1:
	call	_ZN12TmDataCenterC1Ev
.LEHE1:
	movq	%rbx, -40(%rbp)
	movl	$.LC0, %esi
	movl	$_ZSt4cout, %edi
.LEHB2:
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi
	movq	%rax, %rdi
	call	_ZNSolsEPFRSoS_E
	movl	$16, %edi
	call	_Znwm
	movq	%rax, %rbx
	movl	$10, %esi
	movq	%rbx, %rdi
	call	_ZN10slist_nodeIiEC1Ei
	movq	%rbx, -48(%rbp)
	movq	-48(%rbp), %rax
	movq	%rax, -24(%rbp)
	movl	$1, -28(%rbp)
	jmp	.L3
.L6:
	movl	$16, %edi
	call	_Znwm
	movq	%rax, %rbx
	movl	-28(%rbp), %eax
	movl	%eax, %esi
	movq	%rbx, %rdi
	call	_ZN10slist_nodeIiEC1Ei
	movq	%rbx, -56(%rbp)
	jmp	.L4
.L5:
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -24(%rbp)
.L4:
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	testq	%rax, %rax
	jne	.L5
	movq	-24(%rbp), %rax
	movq	-56(%rbp), %rdx
	movq	%rdx, (%rax)
	addl	$1, -28(%rbp)
.L3:
	cmpl	$2, -28(%rbp)
	jle	.L6
	movq	-48(%rbp), %rax
	movq	%rax, %rsi
	movl	$_ZSt4cout, %edi
	call	_ZlsIiERSoS0_P10slist_nodeIT_E
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi
	movq	%rax, %rdi
	call	_ZNSolsEPFRSoS_E
	movq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_Z13reverse_slistIiEP10slist_nodeIT_ES3_
	movq	%rax, -64(%rbp)
	movq	-64(%rbp), %rax
	movq	%rax, %rsi
	movl	$_ZSt4cout, %edi
	call	_ZlsIiERSoS0_P10slist_nodeIT_E
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi
	movq	%rax, %rdi
	call	_ZNSolsEPFRSoS_E
	movl	$0, %eax
	jmp	.L10
.L9:
	movq	%rax, %r12
	movq	%rbx, %rdi
	call	_ZdlPv
	movq	%r12, %rax
	movq	%rax, %rdi
	call	_Unwind_Resume
.LEHE2:
.L10:
	addq	$48, %rsp
	popq	%rbx
	popq	%r12
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE982:
	.globl	__gxx_personality_v0
	.section	.gcc_except_table,"a",@progbits
.LLSDA982:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE982-.LLSDACSB982
.LLSDACSB982:
	.uleb128 .LEHB0-.LFB982
	.uleb128 .LEHE0-.LEHB0
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB1-.LFB982
	.uleb128 .LEHE1-.LEHB1
	.uleb128 .L9-.LFB982
	.uleb128 0
	.uleb128 .LEHB2-.LFB982
	.uleb128 .LEHE2-.LEHB2
	.uleb128 0
	.uleb128 0
.LLSDACSE982:
	.text
	.size	main, .-main
	.section	.text._ZN10slist_nodeIiEC2Ei,"axG",@progbits,_ZN10slist_nodeIiEC5Ei,comdat
	.align 2
	.weak	_ZN10slist_nodeIiEC2Ei
	.type	_ZN10slist_nodeIiEC2Ei, @function
_ZN10slist_nodeIiEC2Ei:
.LFB988:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	movq	-8(%rbp), %rax
	movl	-12(%rbp), %edx
	movl	%edx, 8(%rax)
	movq	-8(%rbp), %rax
	movq	$0, (%rax)
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE988:
	.size	_ZN10slist_nodeIiEC2Ei, .-_ZN10slist_nodeIiEC2Ei
	.weak	_ZN10slist_nodeIiEC1Ei
	.set	_ZN10slist_nodeIiEC1Ei,_ZN10slist_nodeIiEC2Ei
	.section	.rodata
.LC1:
	.string	" "
	.section	.text._ZlsIiERSoS0_P10slist_nodeIT_E,"axG",@progbits,_ZlsIiERSoS0_P10slist_nodeIT_E,comdat
	.weak	_ZlsIiERSoS0_P10slist_nodeIT_E
	.type	_ZlsIiERSoS0_P10slist_nodeIT_E, @function
_ZlsIiERSoS0_P10slist_nodeIT_E:
.LFB990:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$40, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movq	-48(%rbp), %rax
	movq	%rax, -24(%rbp)
	movq	-48(%rbp), %rax
	movl	8(%rax), %edx
	movq	-40(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	_ZNSolsEi
	jmp	.L13
.L14:
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	movl	8(%rax), %ebx
	movq	-40(%rbp), %rax
	movl	$.LC1, %esi
	movq	%rax, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movl	%ebx, %esi
	movq	%rax, %rdi
	call	_ZNSolsEi
.L13:
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	testq	%rax, %rax
	jne	.L14
	movq	-40(%rbp), %rax
	addq	$40, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE990:
	.size	_ZlsIiERSoS0_P10slist_nodeIT_E, .-_ZlsIiERSoS0_P10slist_nodeIT_E
	.section	.text._Z13reverse_slistIiEP10slist_nodeIT_ES3_,"axG",@progbits,_Z13reverse_slistIiEP10slist_nodeIT_ES3_,comdat
	.weak	_Z13reverse_slistIiEP10slist_nodeIT_ES3_
	.type	_Z13reverse_slistIiEP10slist_nodeIT_ES3_, @function
_Z13reverse_slistIiEP10slist_nodeIT_ES3_:
.LFB991:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -40(%rbp)
	cmpq	$0, -40(%rbp)
	sete	%dl
	movq	-40(%rbp), %rax
	movq	(%rax), %rax
	testq	%rax, %rax
	sete	%al
	orl	%edx, %eax
	testb	%al, %al
	je	.L17
	movq	-40(%rbp), %rax
	jmp	.L18
.L17:
	movq	$0, -16(%rbp)
	movq	-40(%rbp), %rax
	movq	%rax, -8(%rbp)
	jmp	.L19
.L20:
	movq	-8(%rbp), %rax
	movq	%rax, -24(%rbp)
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -8(%rbp)
	movq	-24(%rbp), %rax
	movq	-16(%rbp), %rdx
	movq	%rdx, (%rax)
	movq	-24(%rbp), %rax
	movq	%rax, -16(%rbp)
.L19:
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	testq	%rax, %rax
	jne	.L20
	movq	-8(%rbp), %rax
	movq	-16(%rbp), %rdx
	movq	%rdx, (%rax)
	movq	-8(%rbp), %rax
.L18:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE991:
	.size	_Z13reverse_slistIiEP10slist_nodeIT_ES3_, .-_Z13reverse_slistIiEP10slist_nodeIT_ES3_
	.text
	.type	_Z41__static_initialization_and_destruction_0ii, @function
_Z41__static_initialization_and_destruction_0ii:
.LFB1001:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	cmpl	$1, -4(%rbp)
	jne	.L21
	cmpl	$65535, -8(%rbp)
	jne	.L21
	movl	$_ZStL8__ioinit, %edi
	call	_ZNSt8ios_base4InitC1Ev
	movl	$__dso_handle, %edx
	movl	$_ZStL8__ioinit, %esi
	movl	$_ZNSt8ios_base4InitD1Ev, %edi
	call	__cxa_atexit
.L21:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1001:
	.size	_Z41__static_initialization_and_destruction_0ii, .-_Z41__static_initialization_and_destruction_0ii
	.type	_GLOBAL__sub_I_main, @function
_GLOBAL__sub_I_main:
.LFB1002:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$65535, %esi
	movl	$1, %edi
	call	_Z41__static_initialization_and_destruction_0ii
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1002:
	.size	_GLOBAL__sub_I_main, .-_GLOBAL__sub_I_main
	.section	.init_array,"aw"
	.align 8
	.quad	_GLOBAL__sub_I_main
	.hidden	__dso_handle
	.ident	"GCC: (GNU) 4.8.2 20131219 (prerelease)"
	.section	.note.GNU-stack,"",@progbits

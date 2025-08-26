# extern exception_handler
isr_stub_0:
    call exception_handler
    iret
isr_stub_1:
    call exception_handler
    iret
isr_stub_2:
    call exception_handler
    iret
isr_stub_3:
    call exception_handler
    iret
isr_stub_4:
    call exception_handler
    iret
isr_stub_5:
    call exception_handler
    iret
isr_stub_6:
    call exception_handler
    iret
isr_stub_7:
    call exception_handler
    iret
isr_stub_8:
    call exception_handler
    iret
isr_stub_9:
    call exception_handler
    iret
isr_stub_10:
    call exception_handler
    iret
isr_stub_11:
    call exception_handler
    iret
isr_stub_12:
    call exception_handler
    iret
isr_stub_13:
    call exception_handler
    iret
isr_stub_14:
    call exception_handler
    iret
isr_stub_15:
    call exception_handler
    iret
isr_stub_16:
    call exception_handler
    iret
isr_stub_17:
    call exception_handler
    iret
isr_stub_18:
    call exception_handler
    iret
isr_stub_19:
    call exception_handler
    iret
isr_stub_20:
    call exception_handler
    iret
isr_stub_21:
    call exception_handler
    iret
isr_stub_22:
    call exception_handler
    iret
isr_stub_23:
    call exception_handler
    iret
isr_stub_24:
    call exception_handler
    iret
isr_stub_25:
    call exception_handler
    iret
isr_stub_26:
    call exception_handler
    iret
isr_stub_27:
    call exception_handler
    iret
isr_stub_28:
    call exception_handler
    iret
isr_stub_29:
    call exception_handler
    iret
isr_stub_30:
    call exception_handler
    iret
isr_stub_31:
    call exception_handler
    iret

.global isr_stub_table
isr_stub_table:
    .long isr_stub_0
    .long isr_stub_1
    .long isr_stub_2
    .long isr_stub_3
    .long isr_stub_4
    .long isr_stub_5
    .long isr_stub_6
    .long isr_stub_7
    .long isr_stub_8
    .long isr_stub_9
    .long isr_stub_10
    .long isr_stub_11
    .long isr_stub_12
    .long isr_stub_13
    .long isr_stub_14
    .long isr_stub_15
    .long isr_stub_16
    .long isr_stub_17
    .long isr_stub_18
    .long isr_stub_19
    .long isr_stub_20
    .long isr_stub_21
    .long isr_stub_22
    .long isr_stub_23
    .long isr_stub_24
    .long isr_stub_25
    .long isr_stub_26
    .long isr_stub_27
    .long isr_stub_28
    .long isr_stub_29
    .long isr_stub_30
    .long isr_stub_31
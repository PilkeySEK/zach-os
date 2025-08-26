let shit = [
    "isr_no_err_stub",
    "isr_no_err_stub",
    "isr_no_err_stub",
    "isr_no_err_stub",
    "isr_no_err_stub",
    "isr_no_err_stub",
    "isr_no_err_stub",
    "isr_no_err_stub",
    "isr_err_stub",
    "isr_no_err_stub",
    "isr_err_stub",
    "isr_err_stub",
    "isr_err_stub",
    "isr_err_stub",
    "isr_err_stub",
    "isr_no_err_stub",
    "isr_no_err_stub",
    "isr_err_stub",
    "isr_no_err_stub",
    "isr_no_err_stub",
    "isr_no_err_stub",
    "isr_no_err_stub",
    "isr_no_err_stub",
    "isr_no_err_stub",
    "isr_no_err_stub",
    "isr_no_err_stub",
    "isr_no_err_stub",
    "isr_no_err_stub",
    "isr_no_err_stub",
    "isr_no_err_stub",
    "isr_err_stub",
    "isr_no_err_stub"]

let i = 0;
for (let elem in shit) {
    if(elem === "isr_err_stub") {
        console.log(`isr_stub_${i}:\n    call exception_handler\n    iret`);
    }
    else {
        console.log(`isr_stub_${i}:\n    call exception_handler\n    iret`);
    }
    i++;
}
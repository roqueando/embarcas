# debug_timer.gdb — script para debug de timer/ISR no ATtiny85 com simavr + avr-gdb

# Opcional: definir a velocidade de polling / delay entre verificações
set pagination off

file embarcas.elf

# Conectar ao target remoto (ajuste porta se necessário)
target remote :1234

# Opcional: carregar o firmware se o GDB-stub suportar — normalmente não:
load

# Breakpoint principal: start do main
b main
continue

# Depois de iniciar, verificar algumas condições iniciais
echo \n--- Estado inicial ---\n
p/x TCCR0B
p/x TCNT0
p/x TIFR
p/x TIMSK
p/x PORTB
echo ----------------------\n

# Loop de monitoramento — vai imprimir a cada 'c' ou 'si' (step interrupt), etc.
define monitor
    echo \n--- Monitor timer / ISR status ---\n
    display /t TCCR0B
    display /t TCNT0
    display /t TIFR
    display /t TIMSK
    display /t PORTB
    echo -------------------------------\n
    continue
end

# breakpoint na ISR — para ver quando o interrupt dispara
# b TIMER0_COMPA_vect

# Continuar execução e usar monitor após cada pausa
while 1
    monitor
end

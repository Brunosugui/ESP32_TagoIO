# Debugging guide ESP32

Guia para configuração do debugging da placa ESP32 da Espress-if

## Overall

A placa utilizada é a placa de desenvolvimento [ESP32_devkitc_v4](https://docs.espressif.com/projects/esp-idf/en/latest/get-started/get-started-devkitc.html), com um módulo [ESP32-WROVER-B](https://www.espressif.com/sites/default/files/documentation/esp32-wrover-b_datasheet_en.pdf) @ 40MHz & 4Mb flash.

Como esta placa não possui um componente debugger para o pinout JTAG, é necessário utilizar uma placa que o tenha, no caso o ESP-PROG. Então, basta fazer a ligação dos pinos do [ESP-PROG](https://github.com/espressif/esp-iot-solution/blob/master/documents/evaluation_boards/ESP-Prog_guide_en.md) com os pinos JTAG do [ESP32-WROVER-B](https://www.espressif.com/sites/default/files/documentation/esp32-wrover-b_datasheet_en.pdf) (MTDI (IO_12), MTCK (IO_13), MTMS (IO_14), MTDO (IO_15), VDD e GND).

Obs.: o JTAG é a interface de hardware do debug, o OpenOCD é a interface de software

Para que o debug funcione é necessário, primeiro, garantir que o openocd está em execução para interfacear a placa. Para isto, deve-se instalar o OpenOCD (recomendado pelo instalador da ESP-IDF clicando [aqui](https://docs.espressif.com/projects/esp-idf/en/latest/get-started-cmake/windows-setup.html) e baixando o 'ESP-IDF Tools Installer'). Caso já tenha instalado o msys, não é necessário instalar de novo a Toolchain e outras coisas, instalar somente o OpenOCD.

Como o ESP-PROG utiliza um chip FTDI (FT2232HL) é necessário fazer a instalação do driver do mesmo para utilizar a porta COM do computador. O driver da FTDI pode ser obtido [aqui](https://www.ftdichip.com/Drivers/VCP.htm).

Caso haja algum problema com relação à comunicação do módulo, recomenda-se utilizar o Zadig para fazer a troca do driver instalado para um formato reconhecido pelo windows, que pode ser encontrado [aqui](https://zadig.akeo.ie/). Ao executá-lo basta clicar em "`Options`" > "`List All Devices`", selecionar o "`Dual RS232-HS (Interface 0)`" e clicar em Replace Driver.

## Configuração

### Iniciando o OpenOCD

Mover a pasta "`Debug ESP32`" para o diretório onde o OpenOCD foi instalado (por padrão é o diretório "`C:\Program Files\Espressif\ESP-IDF Tools\tools`"), este diretório deve conter os diretórios "`bin`" e "`share`". Após movida a pasta "`Debug ESP32`" deve-se executar o arquivo "`esp_debug.bat`" e uma janela de terminal deverá abrir e mostrar uma mensagem repetidamente, semelhante à:
```
...
Info : Detected debug stubs @ 3ffc4344 on core0 of target 'esp32'
Info : esp32: Debug controller was reset (pwrstat=0x5f, after clear 0x0F).
...
```

### Configuração no Eclipse

Para configurar o Eclipse como sendo a plataforma de Debug do ESP32, é necessário realizar as seguintes configurações:

- em "`Run`" > "`Debug Configuration`", adicionar nova configuração para "`GDB Hardware Debugging`";
- Dar um nome para a configuração;
- na aba "`Main`":
  - em "`Project`" selecionar o projeto;
  - em "`C/C++ Application`" selecionar o arquivo "`.elf`" do projeto, dentro da pasta "`build`";
  - em "`Build (if required) before launching`" checar o "`Disable auto build`";
- na aba "`Debugger`":
  - em "`GDB Command`" colocar "`xtensa-esp32-elf-gdb`";
  - Checar "`Use remote target`";
  - em "`JTAG Device`" selecionar "`Generic TCP/IP`";
  - em "`Host name of IP address`" colocar "`localhost`";
  - em "`Port number`" colocar "`3333`";
- na aba "`Startup`":
  - em "`Initialization Commands`":
    - desmarcar a opção "`Reset and Delay (seconds)`" e "`Halt`";
    - Colocar na caixa de texto os seguintes comandos:
        ```
        mon reset halt
        flushregs
        set remote hardware-watchpoint-limit 2
        ```
  - em "`Load Image and Symbols`" desmarcar "`Load image`";
  - em "`Runtime Options`":
    - marcar "`Set breakpoint at:`" e colocar "`app_main`" no campo;
    - marcar "`Resume`";

* para mais detalhes, verificar [aqui](https://docs.espressif.com/projects/esp-idf/en/latest/api-guides/jtag-debugging/using-debugger.html#jtag-debugging-using-debugger-eclipse).


# Passos para importação do projeto no Eclipse

## Pré-configuração (Windows)

Para programar utilizando a ESP-IDF, é necessário ter o [msys32](https://docs.espressif.com/projects/esp-idf/en/latest/get-started/windows-setup.html) (ambiente de desenvolvimento + toolchain) e a [SDK (esp-idf)](https://docs.espressif.com/projects/esp-idf/en/latest/get-started/index.html#get-started-get-esp-idf) (ferramentas em si) podendo ser obtidos através do site da documentação da [espress-if](https://docs.espressif.com/projects/esp-idf/en/latest/index.html). De acordo com a documentação da espressif, quando o projeto é importado para dentro da pasta do msys seu tempo de compilação fica ligeiramente menor, então, recomenda-se instalar o msys no diretório C. 
Então, fazer o download da SDK (esp-idf) no caminho `C:/msys32/home/[USERNAME]/` e o projeto a ser importado no eclipse no caminho `C:/msys32/home/[USERNAME]/Projects` (eu optei por criar uma pasta (Projects) para os projetos desenvolvidos utilizando a esp-idf, mas não é obrigatório esse diretório).

## No Eclipse

Para mais detalhes, verificar [documentação oficial/eclipse](https://docs.espressif.com/projects/esp-idf/en/latest/get-started/eclipse-setup.html).

### Import

- File -> Import
- Existing Code as Makefile Project
- Selecionar a pasta do projeto
- Pronto!
  
### Configurações do projeto

- Click direito no projeto -> Propriedades
- C/C++ Build
  - Behavior
    - Check Enable parallel build
  - Environment
    - add `BATCH_BUILD = 1`
    - add `IDF_PATH = C:\msys32\home\[USERNAME]\esp-idf`
    - add `PATH = C:\msys32\usr\bin;C:\msys32\opt\xtensa-esp32-elf\bin;C:\msys32\mingw32\bin`
    - *Obs.: deletar outros caminhos da variável `PATH`, deixar somente os caminhos do `msys32`
- C/C++ General
  - Indexer
    - Check `Enable project specific settings`
    - Uncheck `Allow heuristic resolution of includes`
  - Preprocessor Include Paths, Macros etc. / Providers
    - CDT Cross GCC Built-in Compiler Settings
      - `xtensa-esp32-elf-gcc ${FLAGS} -std=c++11 -E -P -v -dD "${INPUTS}"`
    - CDT GCC Build Output Parser
      - `xtensa-esp32-elf-(gcc|g\+\+|c\+\+|cc|cpp|clang)`

### Extras
- Para compilar pela primeira vez algum exemplo, é necessário rodar o `make menuconfig` em um terminal `Mingw32` contido na pasta do `msys32`.
- Para verificar o Output da Serial (Utilizando a UART da placa de desenvolvimento (UART0 definida como padrão para os `printf`) é necessário rodar o `make monitor` em um terminal `Mingw32` contido na pasta `msys32`.
Obs.: O comando `Make` executa, por padrão um arquivo nomeado como `Makefile`, portanto, para rodar o `make menuconfig`, `make monitor`, `make flash`, `make flash monitor`, etc... é necessário estar na pasta do projeto que contenha o arquivo `Makefile`.

- Para facilitar, criar Build Targets -> `all`, `clean` e `flash`
- Importar include paths:
  - clique direito/ Propriedades / C/C++ General
    - Paths and Symbols/Includes
      - Import Settings -> apontar para o arquivo includePaths.xml
- É interessante utilizar a estrutura de projeto sugerida pela espressif, que pode ser consultada na [documentação oficial/build system](https://docs.espressif.com/projects/esp-idf/en/latest/api-guides/build-system.html?highlight=build%20system).

Obs.: os includes variam de acordo com os componentes utilizados da espressif, sendo necessário adicionar alguns dependendo da aplicação.

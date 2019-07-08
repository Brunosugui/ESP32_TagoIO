# ChangeLog TagoIO

Modificações no projeto e datas

## Objetivo final do projeto
- Conexão com a plataforma TagoIO;
- Tornar o projeto um exemplo para integração com qualquer tipo de sensoriamento;

### Objetivos secundários
- Implementação do Bootloader com atualização OTA;
- Comunicação Bluetooth;

## [Bruno]  v1.0 - 21/06/2019
- First commit;
- Modificação do exemplo esp_http_client_example;
- *To do list*:
    - adicionar definições ao example config do menuconfig;
    - definir a conexão com a plataforma Tago;
    - implementar tasks de atualização de dados;
    - realizar ajustes dos includes;

## [Bruno]  v1.1 - 26/06/2019
- Adicionadas definições ao config do menuconfig;
- Ajustes de includes realizados, projeto compilando, porém ainda não executado;
- *To do list*:
    - Testar conexão com a plataforma Tago;
    - Fazer o post de alguns dados de teste;

## [Bruno]  v1.2 - 07/07/2019
- Criada task de eventos;
- Adicionado semaphore para sincronismo de recurso (estado da task Tago);
- Adicionada thread para envio de dados
- *To do list*:
    - rotina de envio de dados para a plataforma Tago
    - Reconexão do wifi caso a task tago esteja em IDLE state
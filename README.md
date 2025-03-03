# ns3-oran-customizable-db

# Estrutura do readme.md
* [Selos Considerados](#selos-considerados)
* [Informações básicas](#informações-básicas)
* [Preocupações com segurança](#preocupações-com-segurança)
* [Instalação](#instalação)
* [Teste mínimo](#teste-mínimo)
* [Experimentos](#experimentos)
* [LICENSE](#license)

# Selos Considerados

Os selos considerados são: Disponíveis, Funcionais e Sustentáveis.

# Informações básicas

Esta seção deve apresentar informações básicas de todos os componentes necessários para a execução e replicação dos experimentos. 
Descrevendo todo o ambiente de execução, com requisitos de hardware e software.

# Dependências

As dependências do ns-3 e das extensões ns3-oran e ns3-ai podem ser instaladas com o gerenciador de pacote apt com o comando:
```shell
apt-get install git build-essential libboost-all-dev pybind11-dev cmake sqlite sqlite3 libsqlite3-dev protobuf-compiler python3 python3-pip doxygen sphinx
```
# Preocupações com segurança

O artefato não apresenta nenhum risco à segurança.

# Instalação

## Instalação do ns-3

```shell
git clone https://gitlab.com/nsnam/ns-3-dev.git
cd ns-3-dev
git checkout -b ns-3.40 ns-3.40
```

## Instalação do ns3-oran-customizable-db

Na pasta "ns-3-dev":
```shell
cd contrib
git clone https://github.com/felip-T/ns3-oran oran
```

## Instalação do ns3-ai (opcional)

Na pasta "ns-3-dev/contrib":
```shell
git clone https://github.com/felip-T/ns3-ai ai
```

## Compilação do ns-3
Na pasta "ns-3-dev":
```shell
./ns3 configure --enable-examples
./ns3
```

# Teste mínimo

Esta seção deve apresentar um passo a passo para a execução de um teste mínimo.
Um teste mínimo de execução permite que os revisores consigam observar algumas funcionalidades do artefato. 
Este teste é útil para a identificação de problemas durante o processo de instalação.

# Experimentos

Esta seção deve descrever um passo a passo para a execução e obtenção dos resultados do artigo. Permitindo que os revisores consigam alcançar as reivindicações apresentadas no artigo. 
Cada reivindicações deve ser apresentada em uma subseção, com detalhes de arquivos de configurações a serem alterados, comandos a serem executados, flags a serem utilizadas, tempo esperado de execução, expectativa de recursos a serem utilizados como 1GB RAM/Disk e resultado esperado. 

Caso o processo para a reprodução de todos os experimento não seja possível em tempo viável. Os autores devem escolher as principais reivindicações apresentadas no artigo e apresentar o respectivo processo para reprodução.

## Reivindicações #X

## Reivindicações #Y

# LICENSE

Apresente a licença.



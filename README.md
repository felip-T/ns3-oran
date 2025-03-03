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

Os selos considerados são: Disponíveis, Funcionais e Sustentáveis e Reprodutíveis.

# Informações básicas

Esta seção deve apresentar informações básicas de todos os componentes necessários para a execução e replicação dos experimentos. 
Descrevendo todo o ambiente de execução, com requisitos de hardware e software.

# Dependências



As dependências do ns-3 e das extensões ns3-oran e ns3-ai podem ser instaladas com o gerenciador de pacote apt com o comando:
```shell
apt-get update
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
git clone https://github.com/felip-t/ns3-oran contrib/oran
```

## Instalação do ns3-ai (opcional)
É recomendado um ambiente virtual Python para a instalação do ns3-ai.
Na pasta "ns-3-dev":
```shell
git clone https://github.com/felip-T/ns3-ai contrib/ai
./ns3 configure --enable-examples
./ns3
pip install stable_baselines3 gymnasium
pip install -e contrib/ai/python_utils
pip install -e contrib/ai/model/gym-interface/py
```

## Compilação do ns-3
Na pasta "ns-3-dev":
```shell
./ns3 configure --enable-examples
./ns3
```

## Dockerfile
Opcionalmente, a ferramenta pode ser utilizada a partir da Dockerfile disponibilizada no diretório "docker".
```shell
git clone https://github.com/felip-T/ns3-oran
cd ns3-oran/docker
docker build -t ns3-oran-customizable-db .
```

Utilizando o contêiner:
```shell
docker run -it --rm ns3-oran-customizable-db:latest
./setupDocker.sh
```

# Teste mínimo

O caso de uso 1, mostrado no artigo, pode ser utilizado como teste mínimo. Para executar o exemplo basta o comando:
```shell
./ns3 run "simple-db-example"
```

# Experimentos

## simple-db-example


## Reivindicações #Y

# LICENSE

Este artefato constrói em cima de um software disponibilizado pelo NIST, que possuí licença própria. Detalhes da licença estão disponíveis no arquivo LICENSE.md.

# Documentação

## Doxygen
A documentação das funcionalidades implementadas pode ser gerada com doxygen:
```shell
cd doc
doxygen
```
O código acima gerará uma pasta chamada "html", o arquivo "index.html" pode ser aberto com um navegador para acessar a documentação.

## Sphinx
Foram adicionadas informações sobre as adições realizadas no manual do ns3-oran.
O manual pode ser compilado com:
```shell
cd doc
make latexpdf
```
O código acima gerará a documentação em "build/latex".

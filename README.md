# ns3-oran-customizable-db

Uma parte essencial no desenvolvimento de aplicações para o controle e
diagnóstico de uma Rede de Acesso via Rádio (\textit{Radio Access Network} --
RAN) é a simulação. É imprescindível a avaliação das soluções propostas em um
cenário simulado próximo à realidade a fim de evitar possíveis falhas na
implementação. O objetivo deste trabalho é adicionar funcionalidades à extensão "ns3-oran" do
simulador de redes "ns-3". As funcionalidades implementadas dão ao usuário a
liberdade para utilizar a extensão sem restrições de quais dados podem ser
enviados ao Near-RT RIC. A capacidade de coleta, armazenamento e análise de
diversos tipos de dados é fundamental no desenvolvimento e implementação de
soluções baseadas em aprendizado de máquina. Assim, as ferramentas desenvolvidas
permitem a criação de cenários de simulações capazes de treinar modelos por
aprendizado por reforço, utilizando métricas de desempenho que antes
eram impossíveis de serem manipuladas pelo simulador.

# Estrutura do readme.md
* [Selos Considerados](#selos-considerados)
* [Informações básicas](#informações-básicas)
* [Preocupações com segurança](#preocupações-com-segurança)
* [Instalação](#instalação)
* [Teste mínimo](#teste-mínimo)
* [Experimentos](#experimentos)
* [LICENSE](#license)
* [Documentação](#documentação)

# Selos Considerados

Os selos considerados são: Disponíveis, Funcionais e Sustentáveis e Reprodutíveis.

# Informações básicas

Os experimentos foram executados em um computador de mesa com o processador AMD Ryzen 5 5700x3D, com 16 GB RAM, e em um notebook com um processador Intel i7 de oitava geração, com 12 GB RAM.

Recomenda-se ao menos 12GB RAM para a execução dos experimentos.
Placa de vídeo não é necessária.

Os experimentos foram executados no OS Ubuntu 22.04. Recomenda-se a execução em contêiner por meio da Dockerfile disponibilizada. Detalhes sobre a execução do contêiner estão na próxima seção.

# Dependências

As dependências do ns-3 e das extensões ns3-oran e ns3-ai podem ser instaladas com o gerenciador de pacote apt-get com o comando:
```shell
apt-get update
apt-get install git build-essential libboost-all-dev pybind11-dev cmake sqlite sqlite3 libsqlite3-dev protobuf-compiler python3 python3-pip doxygen sphinx
```

As versões exatas utlizadas foram:

build-essential=12.9\
libboost-all-dev=1.74.0.3\
pybind11-dev=2.9.1\
cmake=3.22.1\
sqlite=2.8.17\
sqlite3=3.37.2\
libsqlite3-dev=3.37.2\
protobuf-compiler=3.12.4\
python3=3.10.6\
python3-pip=22.0.2\
doxygen=1.9.1\
python3-sphinx=4.3.2

Dependências opcionais (instaladas pelo pip):

stable_baselines3=2.5.0\
gymnasium=1.0.0

# Preocupações com segurança

O artefato não apresenta nenhum risco à segurança.

# Instalação

## Instalação local
### Instalação do ns-3

```shell
git clone https://gitlab.com/nsnam/ns-3-dev.git
cd ns-3-dev
git checkout -b ns-3.40 ns-3.40
```

### Instalação do ns3-oran-customizable-db

Na pasta "ns-3-dev":
```shell
git clone https://github.com/felip-t/ns3-oran contrib/oran
```

### Instalação do ns3-ai (opcional)
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

### Compilação do ns-3
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
Os últimos comandos irão inicializar o contêiner, compilar o ns-3 e instalar as dependências opcionais para a execução do segundo exemplo.

# Teste mínimo

O caso de uso 1, mostrado no artigo, pode ser utilizado como teste mínimo. Para executar o exemplo, basta o comando:
```shell
./ns3 run "simple-db-example"
```

# Experimentos

## simple-db-example

Este exemplo corresponde ao "caso de uso 1" do artigo.
Para executar basta:
```shell
./ns3 run "simple-db-example"
```

O exemplo cria um cenário de simulação com um relatório personalizado que reporta o IPv4 de um equipamento de usuário periodicamente. O programa imprime na tela as queries sqlite feitas ao banco de dados, é possível ver a criação dinâmica da tabela UeIpv4, semelhante ao evidenciado no artigo. Uma explicação mais detalhada deste exemplo está disponível na documentação Sphinx.

O tempo de execução esperado é na ordem de poucos segundos.

## rl-handover

Este exemplo corresponde ao "caso de uso 2" do artigo.
Para fins de revisão de artefatos, este exemplo não pode ser executado em tempo viável, uma vez que o modelo precisou ser treinado por três dias para a obtenção dos resultados mostrados no artigo.

Porém, é possível rodar o experimento para atestar seu funcionamento básico. O experimento é executado atravéz de um arquivo Python, que treina um modelo por aprendizado por reforço com PPO e inicializa um cenário de simulação múltiplas vezes em sequência, coletando observações e tomando ações de controle no cenário.

Foi feito um script para facilitar a execução do experimento, que pode ser utilizado com:
```shell
./run-rl-handover-example.sh
```

Todas as observações recebidas pelo modelo, bem como sua recompensa e a ação tomada, são exibidas na tela.
O exemplo executa até ser interrompido pelo usuário (Ctrl+C).

Mais informações sobre o exemplo, bem como uma ilustração do cenário simulado, estão disponíveis na documentação Sphinx.

# LICENSE

Este artefato constrói em cima de um software disponibilizado pelo NIST, que possui licença própria. Detalhes da licença estão disponíveis no arquivo LICENSE.md.

# Documentação

## Doxygen
A documentação das funcionalidades implementadas pode ser gerada com doxygen:
```shell
cd contrib/oran/doc
doxygen
```
O código acima gerará uma pasta chamada "html", o arquivo "index.html" pode ser aberto com um navegador para acessar a documentação.

## Sphinx
Foram adicionadas informações sobre as adições realizadas no manual do ns3-oran.
O manual pode ser compilado com:
```shell
cd contrib/oran/doc
make latexpdf
```
O código acima gerará a documentação em "contrib/oran/doc/build/latex".

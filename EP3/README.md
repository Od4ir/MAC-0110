# 🖼️ EP3 - Editor de Imagens 

O programa lê um arquivo de uma imagem no formato '.pgm', que é uma especie de matriz com valores numéricos entre 0 e 255, e fornece várias opções de edição dessa imagem, além de permitir que você salve a imagem nova.

#### 📅 Data: Julho de 2022

## 🔗 Dependências:
Para compilar este programa, você precisará do compilador GCC (GNU Compiler Collection). Se você ainda não tiver o GCC instalado, você pode instalá-lo utilizando o seguinte comando no terminal:

#### 🐧 Linux (Debian/Ubuntu):

```bash
sudo apt-get update
sudo apt-get install build-essential
```

## 🔧 Como compilar e rodar:
Para gerar o executável a partir do código:
```bash
gcc EP3.c -o EP3
```
Para executar o programa:
```bash
./EP3
```
Após isso, basta digitar o nome do arquivo no formato '.pgm' e digitar as transformações que deseja aplicar na imagem. Após isso, é possível reverter todas as mudançãs ou salvar a nova imagem transformada em um arquivo '.pmg'. Para visualizar a imagem, recomenda-se os sites:

- [Opção 1](https://kylepaulsen.com/stuff/NetpbmViewer/)
- [Opção 2](https://www.francogarcia.com/pt-br/ferramentas/visualizador-pgm/)

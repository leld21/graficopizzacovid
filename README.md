# O que o código faz:

  Ele lê um arquivo .csv e procura nele dados (nesse caso os sintomas), ajeita eles em um array, pega cada sintoma único e quantas vezes ele aparece no array original, os ordena e por fim os coloca no gráfico pizza.
   

# Lista das coisas necessárias:

- Não se esquecer de reinstalar/modificar o qt para baixar o componente qt Charts (mandei a imagem no grupo), a versão do qt na imagem era 5.15.0 mas atualizei para 5.15.2 para evitar problemas, só selecionar essa versão(qt 5.15.2) e marcar para baixar o qtcharts e o MinGW 8.1.0 (64 bits)

- Baixar o arquivo dados-se.csv pelo link que mandei do drive ( porque não foi possível mandar diretamente pelo sigaa ).

- abrir pelo qt o .pro localizado dentro da pasta graficopizza

- Colocar no ifstream ip a localização do arquivo dados-se.csv (como por exemplo C:/Users/dados-se.csv no windows) ou colocar o arquivo dentro da pasta(que deve ficar na mesma pasta onde foi colocado a pasta graficopizza) build-graficopizza-Desktop_Qt_5_15_2_MinGW_64_bit-Debug. Recomendo o 1 passo.

- todo o codigo está no main.cpp e as classes no mainwindow.h, comentei o que pude.


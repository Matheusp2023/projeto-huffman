% Leitura dos dados do arquivo Lista Encadeada
list_data = dlmread('output_list.txt', '\t');
list_n = list_data(:, 1);
list_comparations = list_data(:, 2);

% Leitura dos dados do arquivo Árvore de Busca Binária
tree_data = dlmread('output_tree.txt', '\t');
tree_n = tree_data(:, 1);
tree_comparations = tree_data(:, 2);

% Cria o gráfico de dispersão (apenas pontos) para a Lista Encadeada (pontos vermelhos e menores)
subplot(1, 2, 1);
scatter(list_n, list_comparations, 10, 'r', 'filled'); % Tamanho 10 e cor vermelha
title('Lista Encadeada');
xlabel('Tamanho de Entrada (n)');
ylabel('Comparações');
grid on;

% Cria o gráfico de dispersão (apenas pontos) para a Árvore de Busca Binária (pontos menores)
subplot(1, 2, 2);
scatter(tree_n, tree_comparations, 10, 'filled'); % Tamanho 10
title('Árvore de Busca Binária');
xlabel('Tamanho de Entrada (n)');
ylabel('Comparações');
grid on;

% Defina os limites desejados para os eixos x e y
xlim([0, 100000]); % Substitua min_x e max_x pelos valores desejados
ylim([0, 100000]); % Substitua min_y e max_y pelos valores desejados

% Ajusta o tamanho da janela de plotagem
set(gcf, 'Position', [100, 100, 1200, 500]);

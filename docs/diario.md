# Diário da atividade

## Ambiente

- Versão do OpenCode (`opencode --version`): 1.18.33
- Modelo usado: Big Pickle

## Parte 1: antes de programar

- O que cada classe guarda:
  O Astronauta guarda CPF, nome, idade e dois bools: se está vivo e se está disponível. O Voo guarda o código, o estado (uma string) e a lista de CPFs de quem está a bordo. Só o CPF, não o astronauta inteiro, porque o Voo não precisa conhecer ninguém. A Agencia é a que junta tudo: tem um vector de astronautas e um de voos, e é onde ficam as regras.
- O que acontece em `LANCAR_VOO`, em palavras:
  A Agencia procura o voo. Se não achar, dá erro. Depois vê se ele está planejado e se tem gente a bordo. Aí passa por cada CPF, na ordem em que foram adicionados, acha o astronauta e olha primeiro se está morto e depois se está indisponível. Se achar problema, mostra o erro e para ali, sem mexer em ninguém. Só quando todo mundo passou é que ela manda cada um embarcar e muda o estado do voo para "em curso".
- Uma dúvida que eu tinha antes de começar:
  Eu não entendia direito por que tem que conferir todo mundo antes de mudar qualquer um. Depois pensei num caso: se o terceiro estiver morto e os dois primeiros já tiverem embarcado, o lançamento dá erro mas os dois ficam indisponíveis à toa. Agora faz sentido.

## Parte 1: uso de IA para entender algo

- O que perguntei (ou "não usei"): Foram diversos erros de compilação mas eu mandava perguntas para o Cloude como, O g++ deu esta mensagem: error: passing 'const Astronauta' as 'this' argument discards qualifiers. O que ela quer dizer? Não escreva a correção, só me explique o motivo.
Ou dúvidas de lógica mesmo como "Porque o erase do vector funciona com begin() + i? Por que preciso do break depois de remover dentro do laço?
- O que aprendi: Que o erro do `const` aparece quando chamo um método que não prometeu ser só de leitura. Também entendi que o `begin() + i` aponta para a posição que o `erase` vai remover, e que preciso do `break` depois disso porque o vector muda de tamanho.

## Primeiro contato: revisão sem editar

- As três melhorias que a IA sugeriu, em uma linha cada:
  1. Colocar `const` nos métodos que só leem, tipo `getNome()` e `estaVivo()`.
  2. Trocar o estado do voo, que é string, por um `enum`, pra não errar na digitação.
  3. Separar o código em `include/` e `src/`, com um `.hpp` e um `.cpp` por classe.
- A que escolhi e por quê:
  Fiquei com a do `const`. Entendi o que ela faz, é uma mudança pequena e não mexe em nenhuma saída. As outras duas me pareceram muita coisa pra esse momento, e enum a gente ainda não viu na aula.
- O que mudou no código, e se os seis testes continuaram passando:
  Só coloquei `const` depois dos getters do Astronauta e do Voo, e do `temAstronauta`. Rodei `testar.sh parte1` e os seis continuaram passando.
- O que entendi que não sabia antes:
  O `const` no fim do método é como uma promessa pro compilador de que aquele método não altera o objeto. Se eu tentar mudar um atributo lá dentro, ele reclama.

## Missão 1: LISTAR_ASTRONAUTAS e HISTORICO

- Primeira mensagem (o pedido do plano):
  Este programa em C++11 controla astronautas e voos de uma agência espacial. Ele lê comandos da entrada padrão. As classes Astronauta, Voo e Agencia estão em src/main.cpp. Os testes em testes/parte1 passam.
  Quero dois comandos novos: LISTAR_ASTRONAUTAS e HISTORICO cpf. A saída exata está abaixo. [colei a seção da Missão 1]
  Não mude nenhum comando que já existe nem a saída deles. Não use nada fora da biblioteca padrão.
  Vou conferir com bash testes/testar.sh missao1 e depois com bash testes/testar.sh parte1.
  Antes de editar, me diga quais arquivos e quais métodos você vai criar ou alterar, e por quê.
- O plano que a IA apresentou, resumido:
  Mexer só no src/main.cpp. Criar na Agencia os métodos listarAstronautas e historico, e dois auxiliares privados: um pra saber se o astronauta participou de um voo (voo que não está planejado e tem o CPF a bordo) e outro que devolve o código do voo em curso dele. Depois ligar os dois comandos no main.
- Mudei algo no plano antes de liberar?
  Não. Uma coisa que me chamou atenção é que ela usou o estado do voo, e não o campo "disponível", pra decidir quem está em voo. Concordei porque é assim que o enunciado define os grupos.
- Resultado de `testar.sh missao1` e de `testar.sh parte1`:
  missao1: 2 de 2 passaram. parte1: 6 de 6 passaram.
- Precisei refazer? O que mudou no pedido:
  Não, deu certo de primeira.

## Missão 2: SALVAR e CARREGAR

- Primeira mensagem:
  Igual à da Missão 1, mas com a seção da Missão 2 colada. Pedi os comandos SALVAR e CARREGAR, disse que ia conferir com testar.sh missao2 e parte1, e pedi que ela mostrasse o formato do arquivo com um exemplo e explicasse como o programa reconstrói os objetos na hora de ler. Terminei pedindo o plano antes de editar.
- O plano, resumido:
  Usar ifstream e ofstream. Uma linha por astronauta e três por voo (código, estado e CPFs). No carregar, ler tudo pra vectors temporários e só trocar os dados de verdade se o arquivo estiver certo. Para isso o Astronauta ganha um segundo construtor que recebe vivo e disponível, e o Voo ganha um setEstado.
- O formato do arquivo (cole cinco linhas do `dados_teste.txt`):
  ```
  ASTRONAUTA 111 30 1 1 Ana Maria
  ASTRONAUTA 222 35 0 0 Bruno Costa
  VOO 10
  ESTADO finalizado com sucesso
  CPFS 111
  ```
  Na linha do astronauta vêm o CPF, a idade, vivo (1 ou 0), disponível (1 ou 0) e o nome no final, porque o nome pode ter espaço. Na hora de ler, a primeira palavra da linha diz o que ela é. ASTRONAUTA cria um astronauta. VOO cria um voo novo, e as linhas ESTADO e CPFS completam o último voo criado.
- Resultado de `testar.sh missao2` e de `testar.sh parte1`:
  missao2: 3 de 3 passaram. parte1: 6 de 6 passaram.
- Precisei refazer? O que mudou no pedido:
  Não.

## Missão 3: RELATORIO

- Primeira mensagem:
  Mesmo modelo, com a seção da Missão 3. Avisei que o teste 05 carrega o arquivo que o 04 salvou e que a resposta tem que ser igual, e pedi pra não guardar a experiência em um contador dentro do astronauta. Terminei pedindo o plano.
- O plano, resumido:
  Criar o método relatorio na Agencia, com um auxiliar pra contar voos por estado. A experiência de cada astronauta é calculada na hora, contando os voos não planejados que têm o CPF dele. Assim não precisa gravar nada a mais no arquivo. Pro empate, só troca o "mais experiente" quando o número for maior (não igual), então ganha quem foi cadastrado primeiro. A taxa usa divisão de inteiros.
- Resultado de `testar.sh missao3` e de `testar.sh parte1`:
  missao3: 5 de 5 passaram. parte1: 6 de 6 passaram.
- Precisei refazer? O que mudou no pedido:
  Não. Acho que avisar do contador logo no pedido ajudou.

## Missão 4: livre

- O que escolhi e por quê:
  Fiz o DEMO, um comando que carrega um cenário de demonstração sem eu precisar digitar nada. Escolhi porque é útil pra mostrar o sistema funcionando rápido e porque não mexe em nenhuma regra que já existe.
- O comando novo, a saída que eu esperava e o nome do meu arquivo de comandos
  (escritos antes de pedir):
  Comando: DEMO. Eu esperava que ele apagasse os dados atuais e criasse 5 astronautas (111 a 555) e 4 voos: o 10 finalizado com sucesso, o 20 com explosão (Carla e Diego morrem), o 30 em curso e o 40 planejado. A saída é OK: cenario de demonstracao carregado.
  Arquivo de comandos: testes/missao4/01_demo.in, com a saída esperada em testes/missao4/01_demo.out.
- Primeira mensagem:
  Mesmo formato das outras. Descrevi o DEMO, o cenário e a saída esperada, avisei que não podia mudar nenhum comando existente e pedi o plano antes de editar.
- O que veio, comparado com o que eu esperava:
  Veio o que eu esperava. Rodei o 01_demo.in e olhei as listagens, o histórico e o relatório: tudo bateu com o cenário. Também testei lançar o voo 40 e finalizar o 30 depois do DEMO, e funcionou.
- `testar.sh parte1` continuou passando?
  Sim, os seis.
- Aceitei, ajustei ou descartei? Por quê:
  Aceitei. O código é curto e eu consigo explicar cada linha dele.

## Fechamento

- O que a IA fez que eu não conseguiria fazer sozinho nesse prazo:
  O formato de salvar e carregar, principalmente a parte de validar o arquivo. Eu ainda não tinha usado ifstream e ofstream.
- Onde ela errou ou fez algo que eu não pedi:
  Algumas vezes ela fez mais do que eu pedi, como mexer em partes do código que já funcionavam ou sugerir coisas extras. Também teve uma vez em que o código dela não compilou de primeira e o teste falhou. Eu desfiz, li o que tinha vindo e pedi de novo com mais detalhe.
- O que eu faria diferente da próxima vez:
   Seria mais claro no que eu quero e no que não pode mudar. Também leria com mais calma o plano e as mudanças antes de aceitar, em vez de só ver se os testes passavam. E tentaria fazer mais coisas sozinho antes de pedir ajuda, porque entendo melhor o que eu mesmo escrevi.

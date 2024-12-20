#ifndef LATEX_OUTPUT_H_
#define LATEX_OUTPUT_H_

static const char* latex_begining = ""
    "\\documentclass[12pt]{article}\n"
    "\\usepackage[utf8]{inputenc}\n"
    "\\usepackage[russian]{babel}\n"
    "\\usepackage{xcolor}\n"
    "\\usepackage{makecell}\n"
    "\\usepackage{amsmath}\n"
    "\\usepackage{amssymb}\n"
    "\\usepackage{cancel}\n"
    "\\usepackage{listings}\n"
    "\\usepackage{tikz}\n"
    "\\linespread{1.5}\n"
    "\\definecolor{codegreen}{rgb}{0,0.6,0}\n"
    "\\definecolor{codegray}{rgb}{0.5,0.5,0.5}\n"
    "\\definecolor{codepurple}{rgb}{0.58,0,0.82}\n"
    "\\definecolor{backcolour}{rgb}{0.95,0.95,0.92}\n"
    "\\usepackage[\n"
    "    ignoreheadfoot,\n"
    "    top=2 cm,\n"
    "    bottom=2 cm,\n"
    "    left=2 cm,\n"
    "    right=2 cm,\n"
    "    footskip=1.0 cm,\n"
    "]{geometry}\n"
    "\\begin{document}\n"
    "\\begingroup\n"
    "    \\centering\n"
    "    \\LARGE Дифференцирование\\\\\n"
    "    \\large \\today \\\\[0.5em]\n"
    "    \\large Лаврущев Иван Б05-431\\par\n"
    "\\endgroup\n"
    "\\tableofcontents\n";

static const char* simplify_latex_beginning[] = {
    "\\section{Упростим крокодила}\n",
    "\\section{Маленько поколдуем}\n",
    "\\section{Посмотрим, что с этим можно сделать}\n",
    "\\section{Хмм, как бы здесь изъебнуться}\n",};

static const char* derivation_latex_beginning[] = {
    "\\section{Ну поехали, малышка}\n",
    "\\section{ПОГНАЛИ}\n",
    "\\section{Давай посчитаем эту хуятину}\n",
    "\\section{Ну давай попробуем свои силы}\n"};

static const char* latex_ending[] = {
    "\\LARGE УРААААААА ПОБЕДА, производная просто опущена как дешёвка\n\\end{document}\n",
    "\\LARGE СОСАТЬ АМЕРИКА, ПРОИЗВОДНАЯ ГОТОВА\n\\end{document}\n",
    "\\LARGE КАК ЖЕ МЫ С ТОБОЙ ЕЁ СДЕЛАЛИ\n\\end{document}\n",
    "\\LARGE ДА УЖ, СТУДЕНТАМ ИЗ ВШЭ ТАКОЕ И НЕ СНИЛОСЬ\n\\end{document}\n"};

static const char* phrases[] = {
    "\\subsection{Любому советскому школьнику очевидно, что}\n",
    "\\subsection{Студентов ПМИ до сих мучает вопрос какого хуя}\n",
    "\\subsection{Хотелось бы знать почему, но боюсь моя микроволновка не в силах осознать, что}\n",
    "\\subsection{Заебало объяснять моим соседям по комнате, что}\n",
    "\\subsection{Ну дальше совсем тривиальная задача, коллеги}\n",
    "\\subsection{А вот здесь нихуя не тривиально}\n",
    "\\subsection{Зачем мне знать, что}\n",
    "\\subsection{Где в жизни мне пригодится, знание о том, что}\n",
    "\\subsection{Продавец пятерочки запросто продифференцирует данное выражение}\n",
    "\\subsection{Кис-кис кис-кис я котик ты котик}\n",
    "\\subsection{АААААААААААААА заебло}\n",
    "\\subsection{Ты реально не можешь понять, что}\n",
    "\\subsection{Как тебя земля вообще носит, если ты не понимаешь, что}\n",
    "\\subsection{Ну такое выражение в детском саду учат дифференцировать}\n",
    "\\subsection{Хм, звучит отнюдь не тривиально}\n",
    "\\subsection{Макс Тимошкин не смог взять эту производную}\n",
    "\\subsection{Хватит сидеть в тик токе, лучше уясни этот момент, коллега}\n",
    "\\subsection{Мама забери меня отсюда}\n",
    "\\subsection{В душе все мы немножко с шизой}\n",
    "\\subsection{А мог бы сейчас в Бауманке чилить, но нет, захотел заниматься этой хуйней}\n",
    "\\subsection{Мяу}\n",
    "\\subsection{АААААААААААА что делать с этой залупой}\n",
    "\\subsection{Какое милое говно}\n",
    "\\subsection{Земля тебе пухом}\n",
    "\\subsection{Наши папы не работают в банках, и мы не катаемся на иномарках}\n",
    "\\subsection{Нас не отправляют учиться в Лондон}\n",
    "\\subsection{Ничего на свете лучше неееету, чем взять производную вот ээээту}\n",
    "\\subsection{Задачка для советских яслей}\n",
    "\\subsection{Пять утра я сижу блять фразы для дифференциатора пишу}\n",
    "\\subsection{Дайте лучше мне пива, а не это говно}\n",
    "\\subsection{Блин жрать охота, может пойти дошик заварить}\n",
    "\\subsection{Что бы посчитать такое... великое}\n",
    "\\subsection{Коллеги не падайте со стульев, тут полный шок}\n",
    "\\subsection{Вы шокированы?}\n",
    "\\subsection{Даже мои соседи посчитали это, неужели ты хуже?}\n",
    "\\subsection{Кто посчитает, тот получит энергосик}\n",
    "\\subsection{Кто не посчитает получит пиздюлей}\n",
    "\\subsection{Не ну что это за рукоблудие}\n"
};

static int simplify_latex_beginning_size   = sizeof(simplify_latex_beginning)/sizeof(simplify_latex_beginning[0]);
static int derivation_latex_beginning_size = sizeof(derivation_latex_beginning)/sizeof(derivation_latex_beginning[0]);
static int latex_ending_size               = sizeof(latex_ending)/sizeof(latex_ending[0]);
static int phrases_size                    = sizeof(phrases)/sizeof(phrases[0]);

#define WriteBinaryOperator(operation)                                   \
    if(node->left)  RecursiveWriteToLatex(tree, node->left, latex_file); \
    fprintf(latex_file, operation);                                      \
    if(node->right) RecursiveWriteToLatex(tree, node->right, latex_file)

#define WriteUnaryOperator(operation, open_bracket, close_bracket)       \
    fprintf(latex_file, operation);                                      \
    fprintf(latex_file, open_bracket);                                   \
    if(node->left)  RecursiveWriteToLatex(tree, node->left, latex_file); \
    fprintf(latex_file, close_bracket)

#define WriteStepToLatex(node, start, ending)                            \
    fprintf(latex_file, start);                                          \
    RecursiveWriteToLatex(tree, node, latex_file);                       \
    fprintf(latex_file, ending);                                         \

#define LatexOutput()                                                    \
    PrintPhrase(latex_file, phrases, phrases_size);                      \
    WriteStepToLatex(node, "$$(", ")'");                                 \
    WriteStepToLatex(diff_result, " = ", "$$\n");

TYPE_OF_ERROR WriteToLatex         (Tree<DifferentiatorValue>* tree, TreeNode<DifferentiatorValue>* node);
TYPE_OF_ERROR RecursiveWriteToLatex(Tree<DifferentiatorValue>* tree, TreeNode<DifferentiatorValue>* node, FILE* latex_file);
TYPE_OF_ERROR PrintValue           (TreeNode<DifferentiatorValue>* node, FILE* latex_file               );
TYPE_OF_ERROR PrintPhrase          (FILE* latex_file, const char* phrase_array[], const size_t size     );
void          BeginLatexFile       ();
void          EndLatexFile         ();

#endif

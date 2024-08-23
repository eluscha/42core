#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include "libft.h"

#include <stdio.h>


typedef enum lex_state
{
    WORD,
    DELIM,
    INSQTS,
    INDQTS
} lex_state;

typedef enum e_toktype
{
    UNDETERM,
    NWLINE,
    PIPE,
    CMD,
    ARGS,
    HEREDOC,
    INPUT,
    OUTPUT,
    BEGIN,
    END,
    SQERR,
    DQERR
}   t_toktype;

typedef struct s_tok
{
    char *word;
    struct s_tok *next;
    t_toktype type;
}   t_tok;

void process_tokens(t_tok *head);


size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (*((char *)s + i) != '\0')
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	bflen;
	size_t	i;

	if (ft_strlen(s) < start)
		bflen = 0;
	else if (ft_strlen(s) - start < len)
		bflen = ft_strlen(s) - start;
	else
		bflen = len;
	ptr = malloc(bflen + 1);
	if (ptr == NULL)
		return (NULL);
	i = start;
	while (i < bflen + start)
	{
		ptr[i - start] = s[i];
		i++;
	}
	ptr[i - start] = '\0';
	return (ptr);
}

t_tok *gen_token(t_toktype type, char *input, int start, int len)
{
    t_tok *token = malloc(sizeof(t_tok));
    token->next = NULL;
    token->type = type;
    token->word = NULL;
    if (type == END || type == BEGIN || type == NWLINE)
        return (token);
    token->word = ft_substr(input, start, len);
    return token; //need to handle if it is NULL  
}

t_tok *lexer(char *input, lex_state state, t_tok *tail)
{
    char c;
     t_tok *head;
    if (!tail)
    {
        tail = gen_token(BEGIN, NULL, 0, 0); // need to protect malloc
        head = tail;
    }
    else
    {
        head = tail->next;
        tail->next = gen_token(NWLINE, NULL, 0, 0);
        tail = tail->next;
    }
    int start = 0;
    int wordlen;
    int i = -1;
    while(input[++i])
    {
        c = input[i];
        if (state == DELIM)
        {
            if (c == ' ' || c == '\t')
                continue;
            state = WORD;
            start = i;
        }
        if (c == '\'')
        {
            if (state == INSQTS)
                state = WORD;
            else if (state == WORD)
                state = INSQTS;
        }
        else if (c == '\"')
        {
            if (state == INDQTS)
                state = WORD;
            else if (state == WORD)
                state = INDQTS;
        }
        if (state == WORD && (c == ' ' || c == '\t' || !input[i+1]))
        {
            state = DELIM;
            wordlen = i - start;
            if (!input[i+1])
                wordlen = i + 1 - start;
            tail->next = gen_token(UNDETERM, input, start, wordlen);
            tail = tail->next;
        }
    }
    if (state == INSQTS)
        tail->next = gen_token(SQERR, input, start, i - start);
    else if (state == INDQTS)
        tail->next = gen_token(DQERR, input, start, i - start);
    else
        tail->next = gen_token(END, NULL, 0, 0);
    tail = tail->next;
    tail->next = head;
    return (tail);
}

int main()
{
    char *input = NULL;
    t_tok *tail;
    t_tok *head;
    t_tok *ptr;

    while (1)
    {
        if (input)
            free(input);
        input = readline("prompt> ");
        if (input == NULL) //will happen with ctrl+D
            break;
        if (*input)
            add_history(input);
        tail = lexer(input, DELIM, NULL);
        while (tail->type == SQERR)
        {
            input = readline("> ");
            if (input == NULL) //will happen with ctrl+D
                break;
            tail = lexer(input, INSQTS, NULL);
        }
        while (tail->type == DQERR)
        {
            input = readline("> ");
            if (input == NULL) //will happen with ctrl+D
                break;
            tail = lexer(input, INDQTS, tail);
        }
        head = tail->next;
        process_tokens(head);
        while (head->type != END)
        {
            if (head->type == BEGIN)
                printf("BEGIN ");
            else if (head->type == NWLINE)
                printf("\n");
            else if (head->type == PIPE)
                printf("PIPE ");
            else
                printf("%s ", head->word);
            if (head->word)
                free(head->word);
            ptr = head->next;
            free(head);
            head = ptr;
        }
        printf("END\n");
        free(head);
    }
}

void process_tokens(t_tok *head)
{
    if (head->type == END)
        return ;
    else if (head->type == BEGIN)
    {
        process_tokens(head->next);
        return ;
    }
    if (ft_strncmp(head->word, "|", 2) == 0)
        head->type = PIPE;
    else if (head->word[0] == '<')
    {
        if (head->word[1] == '<')
            head = input_type(head, 2);
        else
            head = input_type(head, 1);
    }
    //else if (head->word)
    process_tokens(head->next);

}
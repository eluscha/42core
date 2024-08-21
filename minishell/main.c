#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

#include <stdio.h>

typedef enum lex_state
{
    WORD,
    DELIM,
    INSQTS,
    INDQTS,
} lex_state;

typedef enum e_toktype
{
    UNDETERM,
    PIPE,
    CMD,
    ARGS,
    INPUT,
    OUTPUT, 
    END
}   t_toktype;

typedef struct s_tok
{
    char *word;
    struct s_tok *next;
    t_toktype type;
}   t_tok;

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

t_tok *gen_token(char *input, int start, int len)
{
    t_tok *token = malloc(sizeof(t_tok));
    token->next = NULL;
    if (!input)
    {
        token->type = END;
        token->word = NULL;
    }
    else
    {
        token->type = UNDETERM;
        token->word = ft_substr(input, start, len);
    }
    return token; //need to handle if it is NULL somewhere 
}

t_tok *lexer(char *input)
{
    char c;
    lex_state state = DELIM;
    t_tok *token = NULL;
    t_tok *head = NULL;
    int start;
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
            if (!token)
            {
                token = gen_token(input, start, wordlen);
                head = token;
            }
            else
            {
                token->next = gen_token(input, start, wordlen);
                token = token->next;
            }
        }
    }
    if (state == INDQTS || state == INSQTS)
    {
        if (state == INDQTS)
            printf("unexpected EOF while looking for matching \"\n");
        else
            printf("unexpected EOF while looking for matching \'\n");
        if (!token)
        {
            token = gen_token(input, start, i - start);
            head = token;
        }
        else
        {
            token->next = gen_token(input, start, i - start);
            token = token->next;
        }
    }
    if (!token)
    {
        token = gen_token(NULL, 0, 0);
        head = token;
    }
    else
        token->next = gen_token(NULL, 0, 0);
    return (head);
}

int main()
{
    char *input = NULL;
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
        head = lexer(input);
        while (head)
        {
            if (head->type == END)
                printf("END\n");
            else
            {
                printf("%s ", head->word);
                free(head->word);
            }
            ptr = head->next;
            free(head);
            head = ptr;
        }
    }
}
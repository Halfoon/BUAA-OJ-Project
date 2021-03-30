#include<stdio.h>
#include<ctype.h>
#include<string>
#include<string.h>
#include<stdlib.h>
typedef long long ll;
/*
Recursive Descent

<expr> ::= ['+'|'-'] <term> {<'+'|'-'> <term>}
<term> ::= <factor2> {<'*'|'/'|'%'> <factor2>}
<factor2> ::= <factor> [ <'^'> <factor2>]
<factor> ::= <expr> | '(' <expr> ')' | <number>
<number> ::= ['+'|'-'] <unsigned>
<unsigned> ::= <non-zero digit> {<digit>} | '0'
<digit> ::= '0' | '1' | ... | '9'
<non-zero digit> ::= '1' | ... | '9'
*/
struct value_expression {
	static const int maxn = 1010;
	char expr[maxn];
	int global_index;
	ll parse_expr();
	ll parse_term();
	ll parse_factor_2();//由于乘方导致的新优先级引入, 需要多写一层，另外需要注意连续乘方的优先级问题
	ll parse_factor();
	ll parse_number();


	inline void init(char* input) {
		memset(expr, 0, sizeof(expr));
		global_index = 0;
		strcpy(expr, input);
	}

	inline char cur_char() {
		return expr[global_index];
	}

	inline bool is_op_1() {
		return cur_char() == '+' || cur_char() == '-';
	}

	inline bool is_op_2() {
		return cur_char() == '*' || cur_char() == '/' || cur_char() == '%';
	}

	inline bool is_op_3() {
		return cur_char() == '^';
	}

	inline void next() {
		++global_index;
	}

	
}solver;

ll fast_pow(ll a, ll b) {
	ll ret = 1;
	while (b) {
		if (b & 1) ret *= a;
		a *= a;
		b >>= 1;
	}
	return ret;
}

ll value_expression::parse_expr() {
	ll num1 = 0, num2 = 0;
	char op = cur_char();
	if (op == '-') next(), num1 = -1ll * parse_term();
	else num1 = 1ll * parse_term();
	while (is_op_1()) {
		op = cur_char();
		next();
		num2 = parse_term();
		switch (op) {
		case '+': num1 = num1 + num2; break;
		case '-': num1 = num1 - num2; break;
		default: break;
		}
	}
	return num1;
}

ll value_expression::parse_term() {
	ll num1 = 0, num2 = 0;
	char op = 0;
	num1 = parse_factor_2();
	while (is_op_2()) {
		op = cur_char();
		next();
		num2 = parse_factor_2();
		switch (op) {
		case '*': num1 = num1 * num2; break;
		case '/': num1 = num1 / num2; break;
		case '%': num1 = num1 % num2; break;
		default: break;
		}
	}
	return num1;
}

ll value_expression::parse_factor_2() {
	ll num1 = 0, num2 = 0;
	char op = 0;
	num1 = parse_factor();
	if (is_op_3()) next(), num2 = parse_factor_2(), num1 = fast_pow(num1, num2);
	return num1;
}

ll value_expression::parse_factor() {
	ll ret = 0;
	if (cur_char() == '(') {
		next();//skip '('
		ret = parse_expr();
		next();//skip ')'
	}
	else ret = parse_number();
	return ret;
}

ll value_expression::parse_number() {
	ll ret = 0, f = 1;
	if (cur_char() == '-') next(), f = -1;
	else if (cur_char() == '+') next();
	while (isdigit(cur_char())) {
		ret = (ret << 3) + (ret << 1) + (ll)(cur_char() ^ '0');
		next();
	}
	return ret * f;
}

char input[1010];
int main() {
	while (scanf("%s", input) != EOF) {
		std::string s = std::string(input);
		int pos = -1;
		while ((pos = s.find("**")) != s.npos)
			s.replace(pos, 2, "^");
		strcpy(input, s.c_str());
		solver.init(input);
		printf("%lld\n", solver.parse_expr());
	}
}

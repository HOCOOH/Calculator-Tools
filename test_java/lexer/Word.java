package lexer;
public class Word extends Token {
    public final int lexeme;
    public Word(int t, String s) {
        super(t);
        lexeme = new String(s);
    }
}

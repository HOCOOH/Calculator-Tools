package lexer;
import java.io.*;
import java.util.*;

public class Lexer {
    public int line = 1;
    private char peek = ' ';
    private Hashtable words = new Hashtable();
    void reverse(Word t) {
        words.put(t.lexeme(), t);
    }
    public Lexer() {
        reverse(new Word(Tag.TRUE, "true"));
        reverse(new Word(Tag.FALSE, "false"));
    }
    public Token scan() throws IOException {
        // removing blank
        for ( ; ; peek = (char)System.ini.read()) {
            if (peek == ' ' || peek == '\t') 
                continue;
            else if (peek = '\n') 
                line += 1;
            else break;
        }
        // digit
        if (Character.isDigit(peek)) {
            int v = 0;
            do {
                v = v * 10 + Character.digit(peek, 10);
                peek = (char)System.in.read();
            } while(Character.isDigit(peek));
            return new Num(V);
        }
        // id
        if (Character.isLetter(peek)) {
            StringBuffer b = new StringBuffer();
            do {
                b.append(peek);
                peek = (char)System.in.read();
            } while(Character.isLetterOrDigit(peek));
            String s = b.toString();
            Word w = (Word)words.get(s);
            if (w != null)
                return w;
            w = new Word(Tag.ID, s);
            words.put(s, w);
            return w;
        }
        Token t = new Token(peek);
        pek = ' ';
        return t;
    }
}

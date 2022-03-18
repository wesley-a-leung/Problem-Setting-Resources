import java.io.*;
import java.math.*;
import java.util.*;
import java.util.regex.Pattern;

public class JavaValidator {
  public static class Validator {
    private DataInputStream din;
    private String nonWhitespaceToken = "\\S+", nonWhitespaceChar = "\\S", anyLine = ".+";
    private boolean hasLast = false;
    private char last;
    public Validator(InputStream inputStream) {
      din = new DataInputStream(inputStream);
    }
    public Validator(String fileName) throws IOException {
      din = new DataInputStream(new FileInputStream(fileName));
    }
    private void require(boolean expr) throws IOException {
      if (!expr) throw new IOException("Validator Error");
    }
    private byte readByte() throws IOException {
      byte ret = 13;
      while (ret == 13) ret = din.readByte();
      return ret;
    }
    private char peekChar() throws IOException {
      last = hasLast ? last : (char) readByte();
      hasLast = true;
      return last;
    }
    private char getChar() throws IOException {
      char ret = peekChar();
      hasLast = false;
      return ret;
    }
    public int readInt(int minValid, int maxValid) throws IOException {
      StringBuilder token = new StringBuilder();
      while (Character.isDigit(peekChar()) || peekChar() == '-') token.append(getChar());
      int ret = Integer.parseInt(token.toString());
      require(minValid <= ret && ret <= maxValid);
      return ret;
    }
    public int readInt() throws IOException {
      return readInt(Integer.MIN_VALUE, Integer.MAX_VALUE);
    }
    public long readLong(long minValid, long maxValid) throws IOException {
      StringBuilder token = new StringBuilder();
      while (Character.isDigit(peekChar()) || peekChar() == '-') token.append(getChar());
      long ret = Long.parseLong(token.toString());
      require(minValid <= ret && ret <= maxValid);
      return ret;
    }
    public long readLong() throws IOException {
      return readLong(Long.MIN_VALUE, Long.MAX_VALUE);
    }
    public double readDouble(double minValid, double maxValid) throws IOException {
      StringBuilder token = new StringBuilder();
      while (Character.isDigit(peekChar()) || peekChar() == '-' || peekChar() == '.') token.append(getChar());
      double ret = Double.parseDouble(token.toString());
      require(minValid <= ret && ret <= maxValid);
      return ret;
    }
    public double readDouble() throws IOException {
      return readDouble(Double.NEGATIVE_INFINITY, Double.POSITIVE_INFINITY);
    }
    public String readString(String rgx) throws IOException {
      StringBuilder ret = new StringBuilder();
      while (!Character.isWhitespace(peekChar())) ret.append(getChar());
      require(Pattern.matches(rgx, ret));
      return ret.toString();
    }
    public String readString() throws IOException {
      return readString(nonWhitespaceToken);
    }
    public char readChar(String rgx) throws IOException {
      char ret = getChar();
      require(Pattern.matches(rgx, "" + ret));
      return ret;
    }
    public char readChar() throws IOException {
      return readChar(nonWhitespaceChar);
    }
    public String readLine(String rgx) throws IOException {
      StringBuilder ret = new StringBuilder();
      while (peekChar() != '\n') ret.append(getChar());
      require(Pattern.matches(rgx, ret));
      return ret.toString();
    }
    public String readLine() throws IOException {
      return readLine(anyLine);
    }
    public void readSpace() throws IOException {
      require(getChar() == ' ');
    }
    public void readNewLine() throws IOException {
      require(getChar() == '\n');
    }
    public void readEOF() throws IOException {
      try {
        getChar();
        require(false);
      } catch (EOFException e) {}
    }
    public void close() throws IOException {
      if (din == null) return;
      din.close();
    }
  }
  
  private static Validator in = new Validator(System.in);
  private static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));

  public static void main(String[] args) throws Exception {
    in.readEOF();
    in.close();
    out.flush();
    out.close();
  }
}

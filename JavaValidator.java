import java.io.*;
import java.math.*;
import java.util.*;
import java.util.regex.Pattern;

public class JavaValidator {
  public static class PresentationError extends Throwable {}
  public static class IntegerParsingError extends PresentationError {}
  public static class FloatingPointParsingError extends PresentationError {}
  public static class WhitespaceError extends PresentationError {}
  public static class RequirementFailure extends Throwable {}
  public static class IntegerRangeError extends RequirementFailure {}
  public static class FloatingPointRangeError extends RequirementFailure {}
  public static class RegexError extends RequirementFailure {}

  public static class Validator {
    private DataInputStream din;
    private boolean hasLast = false;
    private char last;
    public Validator(InputStream inputStream) {
      din = new DataInputStream(inputStream);
    }
    public Validator(String fileName) throws IOException {
      din = new DataInputStream(new FileInputStream(fileName));
    }
    public void require(boolean expr, Throwable t) throws Throwable {
      if (!expr) throw t;
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
    public int readInt(int minValid, int maxValid) throws Throwable {
      StringBuilder token = new StringBuilder();
      while (Character.isDigit(peekChar()) || peekChar() == '-') token.append(getChar());
      int ret = 0;
      try {
        ret = Integer.parseInt(token.toString());
      } catch (NumberFormatException e) {
        throw new IntegerParsingError();
      }
      require(minValid <= ret && ret <= maxValid, new IntegerRangeError());
      return ret;
    }
    public int readInt() throws Throwable {
      return readInt(Integer.MIN_VALUE, Integer.MAX_VALUE);
    }
    public long readLong(long minValid, long maxValid) throws Throwable {
      StringBuilder token = new StringBuilder();
      while (Character.isDigit(peekChar()) || peekChar() == '-') token.append(getChar());
      long ret = 0;
      try {
        ret = Long.parseLong(token.toString());
      } catch (NumberFormatException e) {
        throw new IntegerParsingError();
      }
      require(minValid <= ret && ret <= maxValid, new IntegerRangeError());
      return ret;
    }
    public long readLong() throws Throwable {
      return readLong(Long.MIN_VALUE, Long.MAX_VALUE);
    }
    public double readDouble(double minValid, double maxValid) throws Throwable {
      StringBuilder token = new StringBuilder();
      while (Character.isDigit(peekChar()) || peekChar() == '-' || peekChar() == '.') token.append(getChar());
      double ret = 0;
      try {
        ret = Double.parseDouble(token.toString());
      } catch (NumberFormatException e) {
        throw new FloatingPointParsingError();
      } catch (NullPointerException e) {
        throw new FloatingPointParsingError();
      }
      require(minValid <= ret && ret <= maxValid, new FloatingPointRangeError());
      return ret;
    }
    public double readDouble() throws Throwable {
      return readDouble(Double.NEGATIVE_INFINITY, Double.POSITIVE_INFINITY);
    }
    public String readString(String rgx) throws Throwable {
      StringBuilder ret = new StringBuilder();
      while (!Character.isWhitespace(peekChar())) ret.append(getChar());
      require(Pattern.matches(rgx, ret), new RegexError());
      return ret.toString();
    }
    public String readString() throws Throwable {
      StringBuilder ret = new StringBuilder();
      while (!Character.isWhitespace(peekChar())) ret.append(getChar());
      return ret.toString();
    }
    public char readChar(String rgx) throws Throwable {
      char ret = getChar();
      require(Pattern.matches(rgx, "" + ret), new RegexError());
      return ret;
    }
    public char readChar() throws Throwable {
      return getChar();
    }
    public String readLine(String rgx) throws Throwable {
      StringBuilder ret = new StringBuilder();
      while (peekChar() != '\n') ret.append(getChar());
      require(Pattern.matches(rgx, ret), new RegexError());
      return ret.toString();
    }
    public String readLine() throws Throwable {
      StringBuilder ret = new StringBuilder();
      while (peekChar() != '\n') ret.append(getChar());
      return ret.toString();
    }
    public void readSpace() throws Throwable {
      require(getChar() == ' ', new WhitespaceError());
    }
    public void readNewLine() throws Throwable {
      require(getChar() == '\n', new WhitespaceError());
    }
    public boolean atEOF() throws Throwable {
      try {
        peekChar();
        return false;
      } catch (EOFException e) {
        return true;
      }
    }
    public void readEOF() throws Throwable {
      try {
        getChar();
        throw new WhitespaceError();
      } catch (EOFException e) {}
    }
    public void close() throws Throwable {
      if (din == null) return;
      din.close();
    }
  }
  
  private static Validator in = new Validator(System.in);
  private static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));

  public static void main(String[] args) throws Throwable {
    in.readEOF();
    in.close();
    out.flush();
    out.close();
  }
}

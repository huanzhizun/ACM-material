import java.util.*;
import java.math.*;

public class Main {
  static final int N = 5000 + 10;
  static BigInteger[] power = new BigInteger[N];

  public static void main(String args[]) {
    Scanner in = new Scanner(System.in);
    int test_count = in.nextInt();
    while (test_count -- > 0) {
      int n = in.nextInt();
      BigInteger answer = BigInteger.ZERO;
      BigInteger comb = BigInteger.ONE;
      for (int i = 0; i < n; ++ i) {
        long x = in.nextLong();
        if (i > 0) {
          comb = comb.multiply(BigInteger.valueOf(n - i)).divide(BigInteger.valueOf(i));
        }
        if ((i & 1) > 0) {
          answer = answer.subtract(comb.multiply(BigInteger.valueOf(x)));
        } else {
          answer = answer.add(comb.multiply(BigInteger.valueOf(x)));
        }
      }
      if (n % 2 == 0) {
        answer = answer.negate();
      }
      System.out.println(answer);
    }
  }
}

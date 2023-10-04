import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;

public class Main {
    
    private static int[] powers = new int[1 << 17];
    
    public static void main(String[] args) {
        int r = 0, n, m;
        try(BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
                BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(System.out))) {
            String[] data = reader.readLine().split(" ");
            n = Integer.parseInt(data[0]);
            m = Integer.parseInt(data[1]);
            int power = 1;
            int logn = 0;
            powers[0] = 0;
            for (int i = 1; i <= n; ++i) {
                if (i == power) {
                    power <<= 1;
                    logn++;
                }
                powers[i] = logn - 1;
            }
            int[][] a = new int[n][logn];
            a[0][0] = Integer.parseInt(data[2]);
            for (int i = 1; i < n; ++i) {
                a[i][0] = (23 * a[i - 1][0] + 21563) % 16714589;
            }
            for (int i = 1; i < logn; ++i) {
                for (int j = 0; j <= n - (1 << i); ++j) {
                    a[j][i] = Math.min(a[j][i - 1], a[j + (1 << (i - 1))][i - 1]);
                }
            }
            int u, v;
            data = reader.readLine().split(" ");
            u = Integer.parseInt(data[0]);
            v = Integer.parseInt(data[1]);
            for (int i = 1; i < m; ++i) {
                if (u <= v) {
                    r = Math.min(a[u - 1][powers[v - u]], a[v - (1 << powers[v - u])][powers[v - u]]);
                } else {
                    r = Math.min(a[v - 1][powers[u - v]], a[u - (1 << powers[u - v])][powers[u - v]]);
                }
                u = ((17 * u + 751 + r + 2 * i) % n) + 1;
                v = ((13 * v + 593 + r + 5 * i) % n) + 1;
            }
            if (u <= v) {
                r = Math.min(a[u - 1][powers[v - u]], a[v - (1 << powers[v - u])][powers[v - u]]);
            } else {
                r = Math.min(a[v - 1][powers[u - v]], a[u - (1 << powers[u - v])][powers[u - v]]);
            }
            writer.write(u + " " + v + " " + r);
            
        } catch (FileNotFoundException e) {
            System.out.println("No such file: " + e.getMessage());
        } catch (IOException e) {
            System.out.println("I/O error: " + e.getMessage());
        }
    }
}

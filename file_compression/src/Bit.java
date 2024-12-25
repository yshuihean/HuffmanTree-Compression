public class Bit {
    String b="";
    int num=0; // 表示二进制数据
    int size=0; // 相当于栈指针

    public static final int BITSIZE = 1024;
    public static final int BYTE = 8;

    public void setBit(int n) {
        num |= (1 << n); // 将第n位置为1
    }

    public void clearBit(int n) {
        num &= ~(1 << n); // 将第n位置为0
    }

    public void changeBit(int n) {
        num ^= (1 << n); // 将第n位切换
    }

    public int getBit(int n) {
        return (num >> n) & 1;
    }

    public void setBits(int m, int n) {
        int mask = ((1 << (n - m + 1)) - 1) << m; // 创建掩码
        num |= mask;
    }

    public void clearBits(int m, int n) {
        int mask = ((1 << (n - m + 1)) - 1) << m;
        num &= ~mask;
    }

    public String getB() {
        return b;
    }

    public void setB(String b) {
        this.b = b;
    }

    public int getSize() {
        return size;
    }

    public void setSize(int size) {
        this.size = size;
    }

    public static void main(String[] args) {
        Bit bit = new Bit();
        bit.num=1;
        bit.num<<=1;
        bit.setBit(0);
        System.out.println(bit.num);
    }
}
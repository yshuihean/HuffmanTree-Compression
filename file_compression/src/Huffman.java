import java.io.*;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Huffman {

    public static class HuffmanNode{
        char sign;
        int weight;
        int left;
        int right;
        int parent;

        public HuffmanNode(char sign, int weight){
            this.sign = sign;
            this.weight = weight;
        }
        public char getSign(){
            return sign;
        }
        public int getWeight(){
            return weight;
        }

        public void setLeft(int left){
            this.left = left;
        }
        public int getLeft(){
            return left;
        }
        public void setRight(int right){
            this.right = right;
        }
        public int getRight(){
            return right;
        }
        public void setParent(int parent){
            this.parent = parent;
        }
        public int getParent(){
            return parent;
        }

    }

    public static class HuffmanCode{
        String code;
        char sign;

        public HuffmanCode(String code, char sign){
            this.code = code;
            this.sign = sign;
        }
        public void setCode(String code){
            this.code = code;
        }
        public void setSign(char sign){
            this.sign = sign;
        }
    }

    public static class HuffmanTree{
        List<HuffmanNode> tree;
        List<HuffmanCode> codes;
            public static void initHT(List<HuffmanNode> HT,int n, int[] w, char[] code) {
                // 初始化哈夫曼树
                HT.add(new HuffmanNode('0', 0));
                for(int i=1;i<=n;i++){
                    HT.add(new HuffmanNode(code[i],w[i]));
                }
                for(int i=n+1;i<2*n;i++){
                    HT.add(new HuffmanNode('0',0));
                }
                for(int i=n+1;i<2*n;i++){
                    int s1=0,s2=0;
                    for(int j=1;j<i;j++){
                        if(HT.get(j).parent==0&&s1==0){
                            s1=j;
                        }
                        else if(HT.get(j).parent==0&&s2==0){
                            s2=j;
                        }
                        else if(HT.get(j).parent==0&& HT.get(s1).weight> HT.get(j).weight){
                            s1=j;
                        }
                        else if(HT.get(j).parent==0&& HT.get(s2).weight> HT.get(j).weight){
                            s2=j;
                        }
                    }
                    HT.get(s1).setParent(i);
                    HT.get(s2).setParent(i);
                    HT.get(i).setLeft(s1);
                    HT.get(i).setRight(s2);
                    HT.get(i).weight= HT.get(s1).weight+ HT.get(s2).weight;
                }
                System.out.println("Huffman Tree建立成功！");
            }
        
            public static void huffmanCoding(List<HuffmanNode> HT, HuffmanCode[] HC, int n) {
                // 哈夫曼编码
                int start,c,f;
                CustomArrayList<Character> cd =new CustomArrayList<>();
                for(int i=0;i<n;i++) {
                    cd.add('\0');
                }
                for(int i=0;i<=n;i++){
                    HuffmanCode hc=new HuffmanCode("",'\0');
                    HC[i]=hc;
                }
                for(int i=1;i<=n;i++){
                    start=n-1;
                    for(c=i,f= HT.get(i).parent; f!=0; c=f,f= HT.get(f).parent){
                        if(HT.get(f).left==c){
                            cd.set(--start,'0');
                        }
                        else cd.set(--start,'1');
                    }
                    CustomArrayList<Character> copy=new CustomArrayList<>(cd.subList(start,n-1));
                    //System.out.println("copy:"+copy);
                    HC[i].code= copy.toString();
                    //System.out.println("code:"+HC[i].code);
                    //toString方法会添加[ , ]需要重写toString方法,具体方法由ai解决（长知识了）
                    copy.clear();
                    HC[i].sign=HT.get(i).sign;
                }
                cd.clear();
                System.out.println("HuffmanCode 编码完成！");
            }
        
            public static void huffmanDecoding(FileInputStream fp, HuffmanTree[] HT, int n) throws IOException {
                // 哈夫曼解码
            }
        }
   
}

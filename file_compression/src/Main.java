import java.io.*;
import java.util.ArrayList;
import java.util.List;

public class Main {
    public static void main(String[] args) throws Exception {
        String dir="resources\\HF.txt";
        File file=new File(dir);
        if(!file.exists()){
            file.createNewFile();
            System.out.println("文件HF.txt为空");
        }

        try (FileWriter fw = new FileWriter(file)) {
            fw.write("aaa\n");
            fw.flush();
            fw.write("123\n");
            fw.flush();
            fw.write("!@#\n");
            fw.flush();
            //fw.close();
        }

        int[] frequency =new int[128];

        try(InputStream in=new FileInputStream(dir)){
            int tempbyte;
            while((tempbyte=in.read())!=-1){
                frequency[tempbyte]++;
                //System.out.println((char)tempbyte);
            }
        }

        dir="resources\\Frequency.txt";
        file=new File(dir);
        int num = 0;
        try(FileWriter cw=new FileWriter(file)) {
            for (int i = 0; i < 128; i++) {
                if (frequency[i] > 0) {
                    num++;
                    if((char)i=='\n'){
                        cw.write("/n "+i+":"+frequency[i]+"\n");
                    }
                    else{
                        cw.write((char)i+" "+i+":"+frequency[i]+"\n");
                    }
                    //System.out.println((char) i +" "+i+ ":" + frequency[i]);
                }
            }
        }
        int[] weight=new int[num+1];
        char[] chars=new char[num+1];
        int j=1;
        for (int i = 0; i < 128; i++) {
            if (frequency[i] > 0) {
                weight[j]=frequency[i];
                chars[j]=(char)i;
                j++;
            }
        }//权值字典统计完成


        List<Huffman.HuffmanNode> HT = new ArrayList<Huffman.HuffmanNode>();
        Huffman.HuffmanCode[] HC=new Huffman.HuffmanCode[num+1];
        Huffman.HuffmanTree.initHT(HT,num,weight,chars);
        /*
        for(int i=1;i<=num;i++){
            if(HT.get(i).sign=='\n'){
                System.out.println("/n");
            }
            else{
                System.out.println(HT.get(i).getSign());
            }
        }
        */
        Huffman.HuffmanTree.huffmanCoding(HT,HC,num);
        dir="resources\\Code.txt";
        file=new File(dir);
        try(FileWriter fw=new FileWriter(file)) {
            for(int i=1;i<=num;i++){
                if(HC[i].sign!='\n'){
                    fw.write(HC[i].sign+":"+HC[i].code+"\n");
                }
                else{
                    fw.write("/n:"+HC[i].code+"\n");
                }
            }
        }
        /*
        for(int i=1;i<=num;i++){
            if(HC[i].sign=='\n'){
                System.out.println("/n "+HC[i].code);
            }
            else{
                System.out.println(HC[i].sign+"  "+HC[i].code);
            }
        }
        */
        dir="resources\\HF.txt";
        String wp="resources\\HuffmanPression.dat";
        file=new File(wp);
        Bit bitbuff=new Bit();

        if(!file.exists()){
            file.createNewFile();
            System.out.println("HuffmanPression已创建");
        }
        try(InputStream in=new FileInputStream(dir);FileOutputStream cw=new FileOutputStream(file)){
            int tempbyte;
            while((tempbyte=in.read())!=-1){
                int i=1;
                while(HC[i].sign!=(char)tempbyte){
                    i++;
                }//找到对应字符
                String code=HC[i].code;
                bitbuff.b=bitbuff.b.concat(code);
                bitbuff.size+=code.length();
                //System.out.println(bitbuff.b);

                if(bitbuff.getSize()>=8){
                    for(int t=0;t<8;t++){
                        if(bitbuff.b.charAt(t)=='0'){
                            bitbuff.num<<=1;
                            bitbuff.clearBit(0);
                        }
                        else if(bitbuff.b.charAt(t)=='1'){
                            bitbuff.num<<=1;
                            bitbuff.setBit(0);
                        }
                        else {
                            System.out.println("压缩编码错误：" + bitbuff.b.charAt(t));
                        }
                        //String binary=Integer.toBinaryString(bitbuff.num);
                        //System.out.println("二进制数"+binary);
                    }
                    //String binary=Integer.toBinaryString(bitbuff.num);
                    //System.out.println(binary);
                    cw.write(bitbuff.num);
                    bitbuff.b=bitbuff.b.substring(8);
                    bitbuff.size-=8;
                    bitbuff.num=0;
                }//if
            }//while
            if(bitbuff.getSize()>0){
                int offset=8-bitbuff.size;//偏移位数
                int mask=1;//掩码
                mask<<=offset-1;
                while(bitbuff.size>0){
                    //printf("%d",bitbuff.size);
                    if(bitbuff.b.charAt(bitbuff.size-1)=='0'){
                        bitbuff.num*=2;//等价于<<=
                        bitbuff.clearBit(0);
                        bitbuff.size--;
                    }
                    else if(bitbuff.b.charAt(bitbuff.size-1)=='1'){
                        bitbuff.num*=2;
                        bitbuff.setBit(0);
                        bitbuff.size--;
                    }
                    else{
                        System.out.println("压缩编码错误：" + bitbuff.b.charAt(bitbuff.size-1));
                        bitbuff.size--;
                    }
                }//while
                for(int i=0;i<offset;i++){
                    bitbuff.num<<=1;
                }
                bitbuff.num|=mask;
            }
            cw.write(bitbuff.num);
            System.out.println("HF文件已经压缩为Compression二进制文件");
        }catch (IOException e){
            e.printStackTrace();
        }//读取完成
    }
}
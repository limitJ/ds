package git.src.java;

import java.io.*;
import java.util.*;

public class J11{
    private static HashMap<String, ArrayList<Book>> hasnmap = new HashMap<>();
    private ArrayList<String> noindex = new ArrayList<>();
    private void create_filterindex() {
        BufferedReader bin = null;
        String lines;
        try {
            try{
                bin = new BufferedReader(new FileReader(new File("./file/filtermap.txt")));
                while (null != (lines = bin.readLine())) {
                    noindex.add(lines);
                }
            }finally {
                assert bin != null;
                bin.close();
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
    private void create_indexmap() {
        BufferedReader bin = null;
        String lines;
            try {
                try{
                    bin = new BufferedReader(new FileReader(new File("./file/book.txt")));
                    while ((lines = bin.readLine()) != null){
                        assert false;
                        String[] list = lines.split(" ");
                        String name = null;
                        for (int i = 1; i < list.length; i++) {
                            if (filter(list[i])) {
                                if (hasnmap.containsKey(list[i])) {
                                    hasnmap.get(list[i]).add(new Book(list[0], lines));
                                } else {
                                    ArrayList<Book> arr = new ArrayList<>();
                                    arr.add(new Book(list[0], lines));
                                    hasnmap.put(list[i],arr);
                                }
                            }
                        }
                    }
                }finally {
                    assert bin != null;
                    bin.close();
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
    }

    private boolean filter(String s) {
        for (String noindex1 : noindex) {
            if (noindex1.toLowerCase().equals(s.toLowerCase())) {
                return false;
            }
        }
        return true;
    }

    public static void main(String[] args) {
        J11 j11 = new J11();
        j11.create_filterindex();
        j11.create_indexmap();
        String in = "quit";
        System.out.println("请输入你需要搜索的书名关键词!输入quit退出!");
        while (!(in = new Scanner(System.in).nextLine()).equals("quit")) {
            if (!hasnmap.containsKey(in)) {
                System.out.println("没有找到书籍!");
            }else{
                System.out.println("为你找到如下书籍");
                for (int i = 0; i < hasnmap.get(in).size(); i++) {
                    System.out.println(hasnmap.get(in).get(i));
                }
            }
            System.out.println("请输入你需要搜索的书名关键词!输入quit退出!");
        }
    }
}
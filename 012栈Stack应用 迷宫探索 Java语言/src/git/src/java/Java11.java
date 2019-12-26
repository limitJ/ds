package git.src.java;

import git.src.stack.Stack;
/*
* 栈应用 迷宫探索
* QQ:582521582
* QQ群: 322085520
* * */
public class Java11{
    public static Object[][] getMap(){
        return new Object[][]{//▨代表墙 ▢代表路 ◉代表老鼠起点位置
                {'▨','▨','▨','▨','▨','▨','▨'},
                {'◉','▢','▢','▢','▢','▢','▨'},
                {'▨','▢','▨','▢','▨','▢','▨'},
                {'▨','▢','▢','▨','▢','▨','▨'},
                {'▨','▨','▢','▨','▢','▨','▨'},
                {'▨','▢','▢','▢','▢','▢','▨'},
                {'▨','▨','▨','▨','▨','▢','▨'},
        };
    }

    private static void print(Object[][] map) {//打印地图
        for (int i = 0; i < map.length; i++) {
            for (int j = 0; j < map[i].length; j++) {
                System.out.print(map[i][j]);
            }
            System.out.println();
        }
    }
    //labyrinth老鼠走迷宫问题
    public static void main(String[] args) {
        Stack<Integer[]> stack = new Stack<>();//栈 存放老鼠坐标
        stack.setAddMaxSize(1024);
        Object [][] maze= getMap();//迷宫为7行*7列 入口坐标1,0  出口6,5
        Object[][] path = getMap();//保存老鼠最终走出去的路径痕迹
        int row = 1,col = 0;//老鼠起点位置标记
        stack.push(new Integer[]{row,col});//起点位置入栈
        System.out.println("初始地图");
        print(maze);
        while(!stack.isEmpty()) {
            if (row == 6 && col == 5) { //找到出路退出
                break;
            } else if (maze[row][col + 1].equals('▢')) { //向右探索
                maze[row][col + 1] = '◉';
                col++;
                stack.push(new Integer[]{row,col});
            } else if (maze[row + 1][col].equals('▢')) { //向下探索
                maze[row + 1][col] = '◉';
                row++;
                stack.push(new Integer[]{row,col});
            } else if (maze[row - 1][col].equals('▢')) { //向上探索
                maze[row - 1][col] = '◉';
                row--;
                stack.push(new Integer[]{row,col});
            } else if (maze[row][col - 1].equals('▢')) { //向左探索
                maze[row][col - 1] = '◉';
                col--;
                stack.push(new Integer[]{row,col});
            } else {//走到死路，就将栈中该位置的点 出栈。
                stack.pop();
                if (stack.isEmpty()) {
                    break;
                }
            }
            row = stack.peek()[0];
            col = stack.peek()[1];
        }
        System.out.println("探索地图走过的所有路径:");
        print(maze);
        Stack<Integer[]> new_stack = new Stack<>();
        while (!stack.isEmpty()) {  //将栈反转 得到老鼠走过的正向轨迹
            new_stack.push(stack.pop());
        }
        while (!new_stack.isEmpty()) {
            path[new_stack.peek()[0]][new_stack.peek()[1]] = '◉';
            new_stack.pop();
        }
        System.out.println("最终老鼠走出去的路径地图");
        print(path);

    }
}
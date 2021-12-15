#include <bits/stdc++.h>
using namespace std;
#define MAXname 100
int n;                //进程数量
int current_time = 0; //当前时间
int q = 0;            //设定的时间片大小
int t = 0;
struct Process //进程结构体，表示进程信息
{
    string name;         //进程名字
    int arrive_time;     //到达时间
    int service_time;    //进程运行时间
    int wait_time;       //进程等待时间
    int remain_time;     //进程剩余运行时间
    int turnaround_time; //周转时间
    int start_time;      //进程开始运行时间
    int end_time;        //进程结束时间
    int time_slice;      //进程时间片
} run_process, p[MAXname];
queue<Process> ready_queue, block_queue; //依次为就绪队列、阻塞队列
bool cmp(Process &a, Process &b)
{
    return a.arrive_time < b.arrive_time;
}
void process_init() //进程初始化
{
    cout << "请输入进程数量" << endl;
    cin >> n;
    cout << "请输入时间片长度" << endl;
    cin >> q;
    for (int i = 0; i < n; i++)
    {
        cout << "请输入第" << i + 1 << "个进程的名字  到达时间  服务时间" << endl;
        cin >> p[i].name >> p[i].arrive_time >> p[i].service_time;
        p[i].remain_time = p[i].service_time;
        p[i].time_slice = q; //设置进程时间片
        p[i].end_time = 0;
    }
    run_process.name = "0"; //当前无进程运行
    sort(p, p + n, cmp);
    for (int i = 0; i < n; i++)
    {
        block_queue.push(p[i]); //将进程加入阻塞队列（未达到则视为阻塞）
    }
}
void nextprocess() //取下一个进程
{
    if (!ready_queue.empty()) //当就绪队列非空时
    {
        run_process = ready_queue.front(); //取下个进程
        ready_queue.pop();
    }
    else //否则将运行进程置为空
        run_process.name = "0";
    run_process.wait_time += current_time - run_process.arrive_time; //计算等待时间
}
int block() //阻塞函数，随机概率阻塞
{
    int a;
    a = rand() % 10;
    return 0;
    if (a >= 0 && a < 3)
    {
        return 1;
    }
    else
        return 0;
}
void process_schedule() //进程调度函数
{
    srand(time(NULL)); //随机数种子
    cout << endl
         << "----------------------------------------RR调度算法----------------------------------------"
         << endl
         << endl;
    cout << "当前时间  "
         << "当前进程  "
         << "进程到达时间  "
         << "进程等待时间  "
         << "进程服务时间  "
         << "剩余运行时间  "
         << "剩余时间片时间"
         << endl;
    while (1)
    {
        if (block_queue.empty() && ready_queue.empty() && run_process.name == "0") //当三个队列均为空时，说明进程全部运行完
            break;                                                                 //结束

        if (!block_queue.empty() && block_queue.front().arrive_time <= current_time)
        {                                                   //阻塞队列非空且队首元素到达时间已到当前时间
            block_queue.front().arrive_time = current_time; //将进入就绪队列的时间作为进程到达时间（针对于阻塞过的进程）
            ready_queue.push(block_queue.front());          //则加入就绪队列
            block_queue.pop();                              //从阻塞队列删除
        }
        if (!ready_queue.empty() && run_process.name == "0") //就绪队列非空和运行进程非空
        {
            run_process = ready_queue.front(); //则从就绪对列取首元素
            ready_queue.pop();                 //从就绪队列删除
        }
        if (run_process.name == "0") //若当前无运行进程，则输出空
        {
            cout << setw(8) << current_time
                 << setw(10) << run_process.name << endl;
            current_time++;
        }
        else
        { //当前有运行进程则输出信息
            cout << setw(8) << current_time
                 << setw(10) << run_process.name
                 << setw(14) << run_process.arrive_time
                 << setw(14) << run_process.wait_time
                 << setw(14) << run_process.service_time
                 << setw(14) << run_process.remain_time
                 << setw(14) << run_process.time_slice
                 << endl;
            current_time++;            //当前时间加1
            run_process.remain_time--; //进程剩余运行时间减1
            run_process.time_slice--;  //进程时间片时间减1

            if (run_process.remain_time == 0) //当进程剩余运行时间为0
            {
                p[t++] = run_process;
                nextprocess(); //取下一个进程
                continue;
            }
            else if (run_process.time_slice == 0) //当进程时间片为0时
            {
                run_process.time_slice = q;             //恢复时间片
                run_process.arrive_time = current_time; //更新到达时间
                ready_queue.push(run_process);          //再次入队

                nextprocess(); //取下一个进程
                continue;
            }
            else if (block()) //当进程有运行时间和时间片时，可能发生阻塞
            {
                cout << "-----------------进程阻塞，切换进程----------------" << endl;
                run_process.arrive_time = current_time; //若发生阻塞，修改当前进程到达时间
                block_queue.push(run_process);          //并加入阻塞队列中
                nextprocess();
            }
        }
    }
}
void print_process_information() //输出进程信息
{
    float sumwait = 0;
    cout << "进程名字  "
         << "服务时间  "
         << "等待时间  "
         << endl;
    for (int i = 0; i < n; i++)
    {
        cout << setw(8) << p[i].name
             << setw(10) << p[i].service_time
             << setw(10) << p[i].wait_time
             << endl;
        sumwait += p[i].wait_time;
    }
    cout << "平均等待时间为：" << setprecision(2) << setiosflags(ios::fixed) << float(sumwait / n) << endl;
}
int main()
{
    process_init();
    process_schedule();
    print_process_information();
    system("pause");
    return 0;
}
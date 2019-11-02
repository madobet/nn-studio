{

int *spike_times;		//记录每个神经元激活的次数 和HH不同Aihara不需要记录每个神经元激活的时刻 故一维
int *activity;			//记录每个神经元的活跃性，不同于激活次数，前后两次相差超过0.5才会增加一次活跃性

int SpikeCount(int nid) const { return spike_times[neuron_id]; }
int ActCount(int nid) const { return activity[neuron_id]; }

double FireRate();		//点火率
double SynchroCap();	//同步能力

double c_AiharaNeuron::FireRate()
{
    double fire = 0;
    for (int i = 0; i<size; i++)
        if (neuron[i].Out()>0.5)
            fire++;
    return fire / size;
}//点火率
double c_AiharaNeuron::SynchroCap()
{
    double sigma = 0;
    double average_xi = 0;
    for (int i = 0; i<size; i++)
    {
        double xi = neuron[i].Out();
        sigma += xi*xi;
        average_xi += xi;
    }
    sigma /= size;
    average_xi /= size;
    sigma -= average_xi*average_xi;
    return sigma;
}//同步能力

}
// 暂时存储部分代码
// 这是关于实验的部分，每产生一个实验应当单独开一个线程出来
// 每个线程对应不用的样本，并持续的更新网络和记录
// 设计信号槽用于和GUI进行交互
// 这是一个持续更新的过程，应当和某个QObject相关
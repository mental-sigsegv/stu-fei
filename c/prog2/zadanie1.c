#include <stdio.h>


int main() {
    double m, T, H, g, vsoft, dt, A, de, df, a, v = 0.0, time = 0.0;
    int s, total = 0, max = 0, tmp_max = 0;

    scanf("%lf %lf %lf %lf %lf %lf", &m, &T, &H, &g, &vsoft, &dt);

    // print importet data
    printf("m=%.3lf\nT=%.3lf\nH=%.3lf\ng=%.3lf\nvsoft=%.3lf\ndt=%.3lf\n", m, T, H, g, vsoft, dt);

    // caculate df
    A = T/m;
    df = ((A-g)*H)/A;
    de = H - df;
    printf("de=%.3lf\n", de);

    while (H > 0) {
        if ((H <= de) && (v<vsoft)) {
            s = 1;
            total++;
            tmp_max++;
            a = A- g;
        } else {
            if (tmp_max > max) {
                max = tmp_max;
            }
            tmp_max = 0;
            s = 0;
            a = -g;
        }

        printf("s=%d h=%08.3lf t=%.3lf v=%.3lf\n", s, H, time, v);

        H = H + v*dt+(a*dt*dt)/2;
        v = v + a*dt;

        time += dt;
    }

    if (tmp_max > max) {
        max = tmp_max;  // in case of not turning off engine
    }

    printf("---Landed---\n");
    printf("h    =%08.3lf\n", H);
    printf("t    =% 8.3lf\n", time);
    printf("v    =% 8.3lf\n", v);
    printf("total=%4d\n", total);
    printf("max  =%4d", max);
}
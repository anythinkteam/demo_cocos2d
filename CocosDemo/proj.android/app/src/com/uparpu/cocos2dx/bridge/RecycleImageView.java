package com.uparpu.cocos2dx.bridge;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Path;
import android.util.AttributeSet;
import android.widget.ImageView;


public class RecycleImageView extends ImageView {

    int mRadiu;
    boolean mIsRadiu;

    public RecycleImageView(Context context) {
        super(context);
        mRadiu = dip2px(getContext(), 5);
    }

    public RecycleImageView(Context context, AttributeSet attrs) {
        super(context, attrs);
        mRadiu = dip2px(getContext(), 5);
    }

    public RecycleImageView(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        mRadiu = dip2px(getContext(), 5);
    }

    public void setNeedRadiu(boolean isRadiu) {
        mIsRadiu = isRadiu;
    }

    @Override
    protected void dispatchDraw(Canvas canvas) {
        try {
            if (mIsRadiu) {
                int width = getWidth();
                int height = getHeight();

                Path path = new Path();
                path.moveTo(mRadiu, 0);

                path.lineTo(width - mRadiu, 0);
                path.quadTo(width, 0, width, mRadiu);

                path.lineTo(width, height - mRadiu);
                path.quadTo(width, height, width - mRadiu, height);

                path.lineTo(mRadiu, height);
                path.quadTo(0, height, 0, height - mRadiu);

                path.lineTo(0, mRadiu);
                path.quadTo(0, 0, mRadiu, 0);
                canvas.clipPath(path);
            }
            super.dispatchDraw(canvas);
        } catch (Exception e) {

        }
    }

    @Override
    protected void onDraw(Canvas canvas) {
        try {
            if (mIsRadiu) {
                int width = getWidth();
                int height = getHeight();

                Path path = new Path();
                path.moveTo(mRadiu, 0);

                path.lineTo(width - mRadiu, 0);
                path.quadTo(width, 0, width, mRadiu);

                path.lineTo(width, height - mRadiu);
                path.quadTo(width, height, width - mRadiu, height);

                path.lineTo(mRadiu, height);
                path.quadTo(0, height, 0, height - mRadiu);

                path.lineTo(0, mRadiu);
                path.quadTo(0, 0, mRadiu, 0);
                canvas.clipPath(path);
            }
            super.onDraw(canvas);
        } catch (Exception e) {

        }
    }

    /**
     * 将dip或dp值转换为px值，保证尺寸大小不变
     *
     * @param dipValue （DisplayMetrics类中属性density）
     * @return
     */
    public static int dip2px(Context context, float dipValue) {
        float scale = context.getResources().getDisplayMetrics().density;
        return (int) (dipValue * scale + 0.5f);
    }


}

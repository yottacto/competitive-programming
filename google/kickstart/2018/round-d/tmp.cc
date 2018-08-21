
void groupRectangles(std::vector<Rect>& rectList, int groupThreshold, double eps,
    std::vector<int>* weights, std::vector<double>* levelWeights)
{
    if (groupThreshold <= 0 || rectList.empty() )
    {
        if (weights )
        {
            size_t i, sz = rectList.size();
            weights->resize(sz);
            for (i = 0; i < sz; i++ )
                (*weights)[i] = 1;
        }
        return;
    }

    std::vector<int> labels;
    int nclasses = partition(rectList, labels, SimilarRects(eps));

    std::vector<Rect> rrects(nclasses);
    std::vector<int> rweights(nclasses, 0);
    std::vector<int> rejectLevels(nclasses, 0);
    std::vector<double> rejectWeights(nclasses, DBL_MIN);
    int i, j, nlabels = (int)labels.size();
    for (i = 0; i < nlabels; i++ )
    {
        int cls = labels[i];
        rrects[cls].x += rectList[i].x;
        rrects[cls].y += rectList[i].y;
        rrects[cls].width += rectList[i].width;
        rrects[cls].height += rectList[i].height;
        rweights[cls]++;
    }

    bool useDefaultWeights = false;

    if ( levelWeights && weights && !weights->empty() && !levelWeights->empty() )
    {
        for (i = 0; i < nlabels; i++ )
        {
            int cls = labels[i];
            if ((*weights)[i] > rejectLevels[cls] )
            {
                rejectLevels[cls] = (*weights)[i];
                rejectWeights[cls] = (*levelWeights)[i];
            }
            else if (( (*weights)[i] == rejectLevels[cls] ) && ( (*levelWeights)[i] > rejectWeights[cls] ) )
                rejectWeights[cls] = (*levelWeights)[i];
        }
    }
    else
        useDefaultWeights = true;

    for (i = 0; i < nclasses; i++ )
    {
        Rect r = rrects[i];
        float s = 1.f/rweights[i];
        rrects[i] = Rect(saturate_cast<int>(r.x*s),
            saturate_cast<int>(r.y*s),
            saturate_cast<int>(r.width*s),
            saturate_cast<int>(r.height*s));
    }

    rectList.clear();
    if (weights )
        weights->clear();
    if (levelWeights )
        levelWeights->clear();

    for (i = 0; i < nclasses; i++ )
    {
        Rect r1 = rrects[i];
        int n1 = rweights[i];
        double w1 = rejectWeights[i];
        int l1 = rejectLevels[i];



        if (n1 <= groupThreshold )
            continue;


        for (j = 0; j < nclasses; j++ )
        {
            int n2 = rweights[j];

            if (j == i || n2 <= groupThreshold )
                continue;
            Rect r2 = rrects[j];

            int dx = saturate_cast<int>( r2.width * eps );
            int dy = saturate_cast<int>( r2.height * eps );

            if (i != j &&
                    r1.x >= r2.x - dx &&
                    r1.y >= r2.y - dy &&
                    r1.x + r1.width <= r2.x + r2.width + dx &&
                    r1.y + r1.height <= r2.y + r2.height + dy &&
                    (n2 > std::max(3, n1) || n1 < 3) )
                break;
        }

        if (j == nclasses )
        {
            rectList.push_back(r1);
            if (weights )
                weights->push_back(useDefaultWeights ? n1 : l1);
            if (levelWeights )
                levelWeights->push_back(w1);
        }
    }
}


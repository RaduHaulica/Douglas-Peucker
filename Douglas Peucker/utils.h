#pragma once

sf::VertexArray createVertexArray(std::vector<sf::Vector2f> v, sf::Color color)
{
	sf::VertexArray va;
	va.setPrimitiveType(sf::PrimitiveType::LinesStrip);
	for (int i = 0; i < v.size(); i++)
	{
		va.append(sf::Vertex(v[i], color));
	}
	return va;
}

float magnitude(sf::Vector2f v)
{
	return std::sqrt(v.x * v.x + v.y * v.y);
}

float distanceBetweenPoints(sf::Vector2f a, sf::Vector2f b)
{
	float distance = std::sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
	return distance;
}

float areaHeron(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c)
{
	float semiperimeter = (distanceBetweenPoints(a, b) + distanceBetweenPoints(a, c) + distanceBetweenPoints(b, c)) / 2.0f;
	//std::cout << "Semiperimeter: " << semiperimeter << std::endl;
	float heron = std::sqrt(semiperimeter * (semiperimeter - distanceBetweenPoints(a, b)) * (semiperimeter - distanceBetweenPoints(a, c)) * (semiperimeter - distanceBetweenPoints(b, c)));
	//std::cout << "Heron: " << heron << std::endl;
	return heron;
}

float dotProduct(sf::Vector2f v1, sf::Vector2f v2)
{
	return v1.x * v2.x + v1.y + v2.y;
}

float distPointToLine(sf::Vector2f line1, sf::Vector2f line2, sf::Vector2f point)
{
	float distance = 2 * areaHeron(line1, line2, point) / distanceBetweenPoints(line1, line2);
	//std::cout << "Distance: " << distance << std::endl;
	return distance;
}

float distPointToLine2(sf::Vector2f line1, sf::Vector2f line2, sf::Vector2f point)
{
	sf::Vector2f AB = line2 - line1;
	AB = { -AB.y, AB.x };
	return std::abs(dotProduct(point - line1, AB / magnitude(AB)));
}

float distPointToLine3(sf::Vector2f line1, sf::Vector2f line2, sf::Vector2f point)
{
	float a = line2.y - line1.y;
	float b = line1.x - line2.x;
	float c = -line1.x * line2.y + line2.x * line1.y;

	return std::abs(a * point.x + b * point.y + c) / std::sqrt(a * a + b * b);
}

sf::Vector2f computeBezierPointDeCasteljau(std::vector<sf::Vector2f> controlPoints, float t)
{
	for (int i = controlPoints.size() - 1; i > 0; i--)
	{
		for (int j = 0; j < i; j++)
		{
			controlPoints[j] = controlPoints[j] * (1 - t) + controlPoints[j + 1] * t;
		}
	}
	return controlPoints[0];
}

std::vector<sf::Vector2f> computeBezier(std::vector<sf::Vector2f> v, int nr_points = 50)
{
	std::vector<sf::Vector2f> vr;
	for (int i = 0; i < nr_points; i++)
	{
		float t = (float)i / (nr_points - 1);
		sf::Vector2f result = computeBezierPointDeCasteljau(v, t);
		//std::cout << "v[" << i << "]= " << result.x << ", " << result.y << std::endl;
		vr.push_back(result);
	}
	return vr;
}

std::vector<sf::Vector2f> algorithm(std::vector<sf::Vector2f> points, float eps)
{
	std::vector<sf::Vector2f> solution;
	if (points.size() <= 2)
	{
		return points;
	}
	else
	{
		float maxDistance{ 0 };
		int index{ -1 };
		for (int i = 1; i < points.size() - 1; i++)
		{
			//std::cout << "D1: " << distPointToLine(points[0], points[points.size() - 1], points[i]) << " D2: " << distPointToLine2(points[0], points[points.size() - 1], points[i]) << " D3: " << distPointToLine3(points[0], points[points.size() - 1], points[i]) << std::endl;
			float distance = distPointToLine3(points[0], points[points.size() - 1], points[i]);
			if (distance > maxDistance)
			{
				maxDistance = distance;
				index = i;
			}
		}

		if (maxDistance > eps)
		{
			//std::cout << "maxDistance > epsilon" << std::endl;
			std::vector<sf::Vector2f> vector1, vector2;
			for (int i = 0; i < points.size(); i++)
			{
				if (i <= index)
					vector1.push_back(points[i]);
				if (i >= index)
					vector2.push_back(points[i]);
			}

			std::vector<sf::Vector2f> part1 = algorithm(vector1, eps);
			std::vector<sf::Vector2f> part2 = algorithm(vector2, eps);
			for (int i = 0; i < part1.size(); i++)
				solution.push_back(part1[i]);
			solution.push_back(points[index]);
			for (int i = 0; i < part2.size(); i++)
				solution.push_back(part2[i]);
		}
		else
		{
			solution.push_back(points[0]);
			solution.push_back(points[points.size() - 1]);
		}
	}
	return solution;
}